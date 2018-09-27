#include "text.h"

#include <iostream>
#include <algorithm>
#include <containers.h>

void AdvancePointerToLetter(const char** ptr, ssize_t offset = 1) {
    while (**ptr && !isalpha(**ptr)) {
        *ptr += offset;
    }
}

bool LineNotEmpty(const char *line) {
    for (const char* c = line; *c; ++c) {
        if (isalpha(*c)) {
            return true;
        }
    }
    return false;
}

std::vector<const char*> BuildEncyclopedia(const Text& text) {
    auto lines = text.GetLines();
    lines.resize(Util::Filter(lines.begin(), lines.end(), LineNotEmpty) - lines.begin());
    std::sort(lines.begin(), lines.end(), [&](const char* line1, const char* line2) {
        for (auto p1 = line1, p2 = line2;;) {
            AdvancePointerToLetter(&p1);
            AdvancePointerToLetter(&p2);

            if ((!*p1 || !*p2) || (*p1 != *p2)) {
                return *p1 < *p2;
            }

            ++p1;
            ++p2;
        }
    });

    return lines;
}

std::vector<const char*> BuildRhymesDict(const Text& text) {
    auto borders = text.GetLineBorders();
    std::vector<size_t> indices;

    indices.reserve(text.GetLinesCount());

    for (size_t i = 0; i < text.GetLinesCount(); ++i) {
        if (LineNotEmpty(borders[i] + 1)) {
            indices.push_back(i);
        }
    }

    indices.shrink_to_fit();

    std::sort(indices.begin(), indices.end(), [&](size_t i1, size_t i2) {
        for (auto p1 = borders[i1 + 1] - 1, p2 = borders[i2 + 1] - 1;;) {
            AdvancePointerToLetter(&p1, -1);
            AdvancePointerToLetter(&p2, -1);

            if ((!*p1 || !*p2) || (*p1 != *p2)) {
                return *p1 < *p2;
            }

            --p1;
            --p2;
        }
    });

    std::vector<const char*> result;
    result.reserve(text.GetLinesCount());

    std::transform(indices.begin(), indices.end(), std::back_inserter(result), [&](size_t index) {
        return borders[index] + 1;
    });

    return result;
}

void OutputLines(const std::vector<const char*>& lines, const char* path) {

    FILE* out = fopen(path, "w");
    if (!out) {
        std::cerr << "Cannot write encyclopedia" << std::endl;
        return;
    }

    for (const auto s : lines) {
        fprintf(out, "%s\n", s);
    }

    fclose(out);
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cerr << "Missing file path. Aborting" << std::endl;
        return 1;
    }

    if (argc < 3) {
        std::cerr << "No output path for encyclopedia. Aborting";
        return 1;
    }

    if (argc < 4) {
        std::cerr << "No output path for rhymes. Aborting";
        return 1;
    }

    Text text(argv[1]);

    if (!text) {
        std::cerr << "Unable to read file. Aborting" << std::endl;
        return 2;
    }

    auto sortedLines = BuildEncyclopedia(text);
    OutputLines(sortedLines, argv[2]);

    auto rhymedLines = BuildRhymesDict(text);
    OutputLines(rhymedLines, argv[3]);

    return 0;
}