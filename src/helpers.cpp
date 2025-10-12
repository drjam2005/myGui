#include <helpers.h>

std::string WrapText(const std::string& text, float maxWidth, float fontSize, float spacing, Font font) {
	std::string wrapped;
    float lineWidth = 0.0f;

    for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        std::string s(1, c);

        if (c == '\n') {
            wrapped += '\n';
            lineWidth = 0.0f;
            continue;
        }

        float charWidth = MeasureTextEx(font, s.c_str(), fontSize, spacing).x;

        if (lineWidth + charWidth > maxWidth && c != ' ') {
            wrapped += '\n';
            lineWidth = 0.0f;

            if (c == ' ') continue;
        }

        wrapped += c;
        lineWidth += charWidth;
    }

    return wrapped;
}

