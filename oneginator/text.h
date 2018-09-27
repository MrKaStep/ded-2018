//
// Created by step on 20.09.18.
//

#ifndef DED_2018_TEXT_H
#define DED_2018_TEXT_H

#include <string>
#include <vector>

/**
 * @brief Class for storing and handling human-readable text
 *
 * This class stores immutable text loaded from file //TODO: add stream constructors
 *
 * It loads file in single read and stores it memory-efficiently.
 */
class Text {
  public:
    /**
     * @param filename - path to load text from
     */
    explicit Text(const char* filename);

    /**
     * @param filename - path to load text from
     */
    explicit Text(const std::string& filename);
    ~Text();

  public:
    /**
     * @brief Checks if object is initialized
     * @return true if text was loaded successfully, false otherwise
     */
    explicit operator bool() const;

    /**
     * Returns line from the text
     * @param index line number
     * @return c-style string
     */
    const char* operator[](size_t index) const;

    /**
     * @return lines number in text
     */
    size_t GetLinesCount() const;

    /**
     * Get pointers to all lines
     * @return vector of c-style strings
     */
    const std::vector<const char*> GetLines() const;

    /**
     * Get all borders between lines ('\0' symbols), including guards before
     * and after first and last lines, respectively
     * @return vector of pointers to all zero symbols in storage
     */
    const std::vector<const char*> GetLineBorders() const;

  private:
    /**
     * Load file from filesystem
     * @param filename
     * @return true if file was loaded successfully, false otherwise
     */
    bool ReadFile(const char* filename);

    /**
     * Build line borders vector, replace '\n' symbols with '\0'
     */
    void Init();

  private:
    char* RawText = nullptr;
    char** LineBorders  = nullptr;

    size_t TextSize = 0;
    size_t BufferSize = 0;
    size_t LinesCount = 0;
};

#endif //DED_2018_TEXT_H
