#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace FontLibrary {

	struct strcGlyph {
		GLuint     GlyphTextureID;  // ID handle of the glyph texture
		glm::ivec2 GlyphSize;       // Size of glyph
		glm::ivec2 GlyphBearing;    // Offset from baseline to left/top of glyph
		GLuint     GlyphAdvance;    // Offset to advance to next glyph
	};

	struct strcFont {
		std::string FontName;
		int FontSize;
		int FontScale;
		std::map<GLchar, strcGlyph> FontGlyphs;
	};

	class FontLoader {

		FT_Library ft;

	public:

		FontLoader() {
			if (FT_Init_FreeType(&ft)) {
				std::cout << "Error Could not init FreeType Library" << std::endl;
				exit(EXIT_FAILURE);
			}
		}

		/// <summary>Generates font glyphs and returns font structure object</summary>
		/// <param name="FontPath">full qualified path to the font, if not root specified this path defaults to next to the executable</param>  
		/// <param name="FontSize">Rendered size of the font in pixels</param>
		/// <param name="GenerateSize">Number of characters to load and generate, for standard ascii specify "128"</param>
		/// <returns>Font structure containing info and bitmap glyph map</returns>  
		FontLibrary::strcFont LoadFont(std::string FontPath, int FontSize, int GenerateSize)
		{
			FT_Face FontFace;
			if (FT_New_Face(ft, FontPath.c_str(), 0, &FontFace)) {
				fprintf(stderr, "Error Could Not Load Font: %s", FontPath.c_str());
				exit(EXIT_FAILURE);
			}

			FT_Set_Pixel_Sizes(FontFace, 0, FontSize);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
			FontLibrary::strcFont generated_font;

			for (GLubyte CharacterIndex = 0; CharacterIndex < GenerateSize; CharacterIndex++)
			{
				if (FT_Load_Char(FontFace, CharacterIndex, FT_LOAD_RENDER))
				{
					fprintf(stderr, "Error FreeType Could Not Load Glyph Num: %i... Skipping", CharacterIndex);
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

				FontLibrary::strcGlyph newGlyph;

				newGlyph.GlyphTextureID = texture;
				newGlyph.GlyphSize = glm::ivec2(FontFace->glyph->bitmap.width, FontFace->glyph->bitmap.rows);
				newGlyph.GlyphBearing = glm::ivec2(FontFace->glyph->bitmap_left, FontFace->glyph->bitmap_top);
				newGlyph.GlyphAdvance = FontFace->glyph->advance.x;

				generated_font.FontGlyphs.insert(std::pair<GLchar, FontLibrary::strcGlyph>(CharacterIndex, newGlyph));
				generated_font.FontScale = GenerateSize;
				generated_font.FontName = FontFace->family_name;
				generated_font.FontSize = FontSize;
			}
			glBindTexture(GL_TEXTURE_2D, 0);
			FT_Done_Face(FontFace);
			FT_Done_FreeType(ft);

			return generated_font;
		}

	};

	class FontRenderer
	{
		strcFont _FontFace;
		GLuint _shader;
		int _ViewportWidth;
		int _ViewportHeight;
		GLuint VAO, VBO;

	public:

		FontRenderer(int ViewportWidth, int ViewportHeight, GLuint ShaderHandle, strcFont FontFace)
		{
			_ViewportWidth = ViewportWidth;
			_ViewportHeight = ViewportHeight;
			_FontFace = FontFace;
			_shader = ShaderHandle;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void RenderText(string text, GLfloat Xpos, GLfloat Ypos, GLfloat Size, glm::vec3 Color)
		{
			glUseProgram(_shader);
			glUniform3f(glGetUniformLocation(_shader, "textColor"), Color.x, Color.y, Color.z);
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(VAO);

			// Iterate through all characters
			std::string::const_iterator c;
			for (c = text.begin(); c != text.end(); c++)
			{
				FontLibrary::strcGlyph ch = _FontFace.FontGlyphs[*c];

				GLfloat xpos = Xpos + ch.GlyphBearing.x * Size;
				GLfloat ypos = Ypos - (ch.GlyphSize.y - ch.GlyphBearing.y) * Size;

				GLfloat w = ch.GlyphSize.x * Size;
				GLfloat h = ch.GlyphSize.y * Size;
				// Update VBO for each character
				GLfloat vertices[6][4] = {
					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos,     ypos,       0.0, 1.0 },
					{ xpos + w, ypos,       1.0, 1.0 },

					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos + w, ypos,       1.0, 1.0 },
					{ xpos + w, ypos + h,   1.0, 0.0 }
				};
				// Render glyph texture over quad
				glBindTexture(GL_TEXTURE_2D, ch.GlyphTextureID);
				// Update content of VBO memory
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				// Render quad
				glDrawArrays(GL_TRIANGLES, 0, 6);
				// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
				Xpos += (ch.GlyphAdvance >> 6) * Size; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
			}
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	};

}