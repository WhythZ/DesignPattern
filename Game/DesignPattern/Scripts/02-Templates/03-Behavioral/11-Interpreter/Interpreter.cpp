#include "Interpreter.h"

#include <string>

#include <imgui_stdlib.h>
#include <SDL2_gfxPrimitives.h>

// Lua�ٷ���վ��https://lua.org/
// Lua�ٷ����Ϻϼ���https://lua.org/docs.html
// Lua5.4�ο��ֲ᣺https://lua.org/manual/5.4/

static std::string strBufferPrint;
static SDL_Renderer* gRenderer = nullptr;

static int APIPrint(lua_State* _luaState)
{
	strBufferPrint += luaL_checkstring(_luaState, 1);
	strBufferPrint += "\n";

	return 0;
}

static int APISetDrawColor(lua_State* _luaState)
{
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(gRenderer, (Uint8)luaL_checkinteger(_luaState, 1), (Uint8)luaL_checkinteger(_luaState, 2), 
		(Uint8)luaL_checkinteger(_luaState, 3), (Uint8)luaL_checkinteger(_luaState, 4));

	return 0;
}

static int APIDrawCircle(lua_State* _luaState)
{
	SDL_Color _colorPainter;
	SDL_GetRenderDrawColor(gRenderer, &(_colorPainter.r), &(_colorPainter.g), &(_colorPainter.b), &(_colorPainter.a));
	filledCircleRGBA(gRenderer, (Sint16)luaL_checkinteger(_luaState, 1), (Sint16)luaL_checkinteger(_luaState, 2), 
		(Sint16)luaL_checkinteger(_luaState, 3), _colorPainter.r, _colorPainter.g, _colorPainter.b, _colorPainter.a);

	return 0;
}

static int APIDrawRectangle(lua_State* _luaState)
{
	SDL_Rect _rect =
	{
		(int)luaL_checkinteger(_luaState, 1),
		(int)luaL_checkinteger(_luaState, 2),
		(int)luaL_checkinteger(_luaState, 3),
		(int)luaL_checkinteger(_luaState, 4)
	};
	SDL_RenderFillRect(gRenderer, &_rect);

	return 0;
}

InterpreterPattern::InterpreterPattern(SDL_Renderer* _renderer)
{
	gRenderer = _renderer;

	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 370, 370);

	ImGuiIO& _ioImGui = ImGui::GetIO();
	fontCode = _ioImGui.Fonts->AddFontFromFileTTF(R"(resources\SarasaMonoSC-Regular.ttf)", 18.0f, nullptr, _ioImGui.Fonts->GetGlyphRangesChineseSimplifiedCommon());

	TextEditor::LanguageDefinition _langDef = TextEditor::LanguageDefinition::Lua();
	{
		TextEditor::Identifier _idSetDrawColor;
		_idSetDrawColor.mDeclaration = u8"set_draw_color(r, g, b, a)�����û�ͼ��ɫ";
		_langDef.mIdentifiers.insert(std::make_pair(std::string("set_draw_color"), _idSetDrawColor));
		TextEditor::Identifier _idDrawCircle;
		_idDrawCircle.mDeclaration = u8"draw_circle(x, y, r)��ʹ�õ�ǰ��ͼ��ɫ�������Բ";
		_langDef.mIdentifiers.insert(std::make_pair(std::string("draw_circle"), _idDrawCircle));
		TextEditor::Identifier _idDrawRectangle;
		_idDrawRectangle.mDeclaration = u8"draw_rectangle(x, y, w, h)��ʹ�õ�ǰ��ͼ��ɫ����������";
		_langDef.mIdentifiers.insert(std::make_pair(std::string("draw_rectangle"), _idDrawRectangle));
	}
	codeEditor.SetLanguageDefinition(_langDef);
	codeEditor.SetShowWhitespaces(false);
	codeEditor.SetText(u8R"(-- Lua �ű��������Զ���ķ�����
-- print(str)�������̨����ַ���
-- set_draw_color(r, g, b, a)�����û�ͼ��ɫ
-- draw_circle(x, y, r)��ʹ�õ�ǰ��ͼ��ɫ�������Բ
-- draw_rectangle(x, y, w, h)��ʹ�õ�ǰ��ͼ��ɫ����������

-- ���Խű��Ļ�ͼ����
function test_draw()
	set_draw_color(228, 94, 50, 225)
	draw_circle(125, 125, 100)
	
	set_draw_color(0, 123, 67, 200)
	draw_rectangle(100, 145, 200, 100)

	set_draw_color(25, 68, 142, 155)
	draw_circle(300, 225, 50)

	set_draw_color(162, 32, 65, 95)
	draw_rectangle(280, 25, 55, 275)
end

-- ���Խű����������
function test_print()
	print(string.lower("HELLO WORLD"))
	print("current time: "..os.date("%Y-%m-%d %H:%M:%S", time or os.time()))
end

test_draw()
test_print()
	)");
}

InterpreterPattern::~InterpreterPattern()
{
	SDL_DestroyTexture(textureTarget);
}

void InterpreterPattern::OnUpdate(float delta)
{
	static const ImVec2 _sizeButton = { ImGui::GetContentRegionAvail().x, 30 };
	if (ImGui::Button(u8"ִ �� �� ��", _sizeButton))
	{
		lua_State* _luaState = luaL_newstate();
		luaL_openlibs(_luaState);

		lua_pushcfunction(_luaState, APIPrint);
		lua_setglobal(_luaState, "print");
		lua_pushcfunction(_luaState, APISetDrawColor);
		lua_setglobal(_luaState, "set_draw_color");
		lua_pushcfunction(_luaState, APIDrawCircle);
		lua_setglobal(_luaState, "draw_circle");
		lua_pushcfunction(_luaState, APIDrawRectangle);
		lua_setglobal(_luaState, "draw_rectangle");

		strBufferPrint = u8"[��ʼִ��]\n==============\n";

		SDL_SetRenderTarget(gRenderer, textureTarget);
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);

		if (luaL_dostring(_luaState, codeEditor.GetText().c_str()) != LUA_OK)
		{
			strBufferPrint += u8"\n[ִ��ʧ��]\n==============\n";
			strBufferPrint += lua_tostring(_luaState, -1);
		}

		SDL_SetRenderTarget(gRenderer, nullptr);

		lua_close(_luaState);
	}

	{
		ImGui::PushFont(fontCode);
		static const ImVec2 size_code_editor = { 350, ImGui::GetContentRegionAvail().y };
		codeEditor.Render("code_editor", size_code_editor, true);
		ImGui::PopFont();
	}
	ImGui::SameLine();
	{
		ImGui::BeginGroup();
		{
			ImGui::TextUnformatted(u8"��ͼ���ݣ�");
			static const ImVec2 size_paint_result = { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().x };
			ImGui::BeginChild("paint_result", size_paint_result, ImGuiChildFlags_Border);
			ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
			ImGui::EndChild();
		}
		ImGui::TextUnformatted(u8"����̨�����");
		ImGui::InputTextMultiline("##print_result", &strBufferPrint, ImGui::GetContentRegionAvail(), ImGuiInputTextFlags_ReadOnly);
		ImGui::EndGroup();
	}

}
