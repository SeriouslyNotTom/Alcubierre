#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <glm/glm.hpp>
#include <map>
#include <stdlib.h>
#include <locale>
#include <algorithm>
#include <alcubierre/libraries/io/FileIO.h>

using namespace std;

namespace Font {

	struct Glyph {
		GLuint TextureID;
		glm::ivec2 Size;
		glm::ivec2 Bearing;
		GLuint Advance;
	};

	struct GlyphSet {
		int Size;
		std::map<GLchar, Glyph> Glyphs;
	};

	struct GeneratedFontFace {
		string Name;
		string AsciiSetSize;
		int SizeMin;
		int SizeMax;
		std::map<int, GlyphSet> GlpyhSets;
	};

	class FontLibrary {

	private:
		FT_Library ft;

	public:
		std::map<string, GeneratedFontFace> FontStorage;
		GeneratedFontFace FallbackFont;
		int NumberOfFontsLoaded;
		int GenerateMinSize = 1;
		int GenerateMazSize = 100;
		int GenerateAsciiSetSize = 255;

		FontLibrary()
		{
			if (FT_Init_FreeType(&ft)) {
				fprintf(stderr, "Could not initialize freetype\n");
				exit(EXIT_FAILURE);
			}

			//load fallback font
			char* font = "fonts / arial.ttf";
			char* path = new char[strlen(ASSET_PATH) + strlen(font)];
			strcpy(path, ASSET_PATH);
			strcat(path, font);
			if (LoadFontByPath(path))
			{
				FallbackFont = FontStorage["arial"];
			}
			else {
				throw exception("No default font");
			}
			

		}
		
		bool LoadFontByName(string fontname)
		{

		}

		bool LoadFontByPath(string fontpath)
		{
			FT_Face FontFace;
			if (FT_New_Face(ft, fontpath.c_str(), 0, &FontFace)) {
				fprintf(stderr, "Error Could Not Load Font: %s\n", fontpath.c_str());
				exit(EXIT_FAILURE);
			}
			int test_size = 48;

			GeneratedFontFace generated_font;
			generated_font.AsciiSetSize = GenerateAsciiSetSize;
			generated_font.Name = FontFace->family_name;
			GlyphSet test_glyphs;
			test_glyphs.Size = test_size;

			FT_Set_Pixel_Sizes(FontFace, 0, test_size);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction


			for (GLubyte CharacterIndex = 0; CharacterIndex < GenerateAsciiSetSize; CharacterIndex++)
			{
				//fprintf(stdout, "characterindex: %i\n", CharacterIndex);
				if (FT_Load_Char(FontFace, CharacterIndex, FT_LOAD_RENDER))
				{
					fprintf(stderr, "Error FreeType Could Not Load Glyph Num: %i... Skipping\n", CharacterIndex);
					continue;
				}

				GLuint texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					FontFace->glyph->bitmap.width,
					FontFace->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					FontFace->glyph->bitmap.buffer
				);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				Glyph newGlyph;

				newGlyph.TextureID = texture;
				newGlyph.Size = glm::ivec2(FontFace->glyph->bitmap.width, FontFace->glyph->bitmap.rows);
				newGlyph.Bearing = glm::ivec2(FontFace->glyph->bitmap_left, FontFace->glyph->bitmap_top);
				newGlyph.Advance = FontFace->glyph->advance.x;

				test_glyphs.Glyphs.insert(std::pair<GLchar, Glyph>(CharacterIndex, newGlyph));

			}
			glBindTexture(GL_TEXTURE_2D, 0);
			FT_Done_Face(FontFace);
			//FT_Done_FreeType(ft);
			
			generated_font.GlpyhSets.insert(std::pair<int, GlyphSet>(test_size, test_glyphs));
			string font_name = generated_font.Name;
			std::transform(font_name.begin(), font_name.end(), font_name.begin(), ::tolower);
			FontStorage.insert(std::pair<string, GeneratedFontFace>(font_name, generated_font));

		}

		bool LoadFontByMemory(INT_PTR memaddr, int memlength)
		{

		}

		bool DoesFontExist(string fontname)
		{
			std::transform(fontname.begin(), fontname.end(), fontname.begin(), ::tolower);
			bool exists = this->FontStorage.count(fontname);
			return exists;
		}

		GeneratedFontFace TryGetFont(string fontname)
		{
			if (DoesFontExist(fontname))
			{
				return this->FontStorage[fontname];
			}
			else {
				return this->FallbackFont;
			}
		}

	};

	class FontRenderer {
		
	public:
		FontLibrary _FontLib;

		FontRenderer(FontLibrary fontlib)
		{
			_FontLib = fontlib;
		}

		void RenderFontInContext(string fontname, int x, int y, int size, string text)
		{

			size_t testsize = _FontLib.FontStorage.count(fontname);
			GeneratedFontFace renderfont = _FontLib.FontStorage[fontname];
			
		}

		void RenderStringToTexture(string fontname)
		{

		}

	};

}