#include <helpers.h>

std::string WrapText(const std::string& text, float maxWidth, float fontSize, float spacing, Font font) {
    std::stringstream ss(text);
    std::string word;
    std::string wrapped;
    float lineWidth = 0.0f;

    while (ss >> word) {
        std::string withSpace = word + " ";
        float wordWidth = MeasureTextEx(font, withSpace.c_str(), fontSize, spacing).x;

        if (wordWidth > maxWidth) {
            for (char c : word) {
                std::string s(1, c);
                float charWidth = MeasureTextEx(font, s.c_str(), fontSize, spacing).x;

                if (lineWidth + charWidth > maxWidth) {
                    wrapped += "\n";
                    lineWidth = 0.0f;
                }
                wrapped += c;
                lineWidth += charWidth;
            }
            wrapped += " ";
            lineWidth += MeasureTextEx(font, " ", fontSize, spacing).x;
        } 
        else if (lineWidth + wordWidth > maxWidth) {
            wrapped += "\n" + word + " ";
            lineWidth = wordWidth;
        } 
        else {
            wrapped += word + " ";
            lineWidth += wordWidth;
        }
    }

    return wrapped;
}

