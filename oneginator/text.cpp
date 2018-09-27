#include <file.h>
#include <stdexcept>
#include "text.h"

Text::Text(const char *filename) {
    if (ReadFile(filename)){
        Init();
    }
}

Text::Text(const std::string &filename)
    : Text(filename.data())
{
}

Text::~Text() {
    if (!!RawText) {
        free(RawText);
    }
}

Text::operator bool() const {
    return !!RawText;
}

const char* Text::operator[](size_t index) const {
    if (index >= LinesCount) {
        throw std::runtime_error("Line index out of bounds");
    }

    return LineBorders[index] + 1;
}

size_t Text::GetLinesCount() const {
    return LinesCount;
}

const std::vector<const char*> Text::GetLines() const {
    std::vector<const char*> result;

    result.reserve(LinesCount);
    for (size_t i = 0; i < LinesCount; ++i) {
        result.push_back(LineBorders[i] + 1);
    }

    return result;
}

const std::vector<const char*> Text::GetLineBorders() const {
    return std::vector<const char*>(LineBorders, LineBorders + LinesCount + 1);
}

bool Text::ReadFile(const char *filename) {
    auto file = fopen(filename, "rb");
    if (!file) {
        return false;
    }

    size_t fileSize = Util::GetFileSize(filename);
    TextSize = fileSize;
    BufferSize = fileSize + 2;
    RawText = (char*)calloc(BufferSize, sizeof(char));

    size_t bytesRead = fread(RawText + 1, sizeof(char), fileSize, file);
    if (bytesRead != fileSize) {
        free(RawText);
        RawText = nullptr;
        return false;
    }

    fclose(file);
    return true;
}

void Text::Init() {
    for (size_t i = 0; i < BufferSize; ++i) {
        if (RawText[i] == '\n') {
            ++LinesCount;
            RawText[i] = '\0';
        }
    }

    LineBorders = (char**)calloc(LinesCount + 1, sizeof(char*));

    size_t currentBorder = 0;
    for (size_t i = 0; i < BufferSize; ++i) {
        if (!RawText[i]) {
            LineBorders[currentBorder++] = RawText + i;
        }
    }
}

