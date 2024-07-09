#ifndef SENECA_TEXTFILE_H__
#define SENECA_TEXTFILE_H__
#include <iostream>
namespace seneca {
#define DEF_PAGE_SIZE 15
    // LINE ------------------------------------------
    class Line {
      char* m_value{ nullptr };
    public:
        Line();
        ~Line();
        operator const char* () const;
        Line& operator=(const char* lineContent);
        Line(const Line&) = delete; // Disallow copying
        Line& operator=(const Line&) = delete;
        friend class TextFile;
   };
   // TEXTFILE ------------------------------------------
    class TextFile {
        Line* m_textLines;
        char* m_filename;
        unsigned m_noOfLines;
        unsigned m_pageSize;

        void setEmpty();
        void setFilename(const char* fname, bool isCopy = false);
        void setNoOfLines();
        void loadText();
        void saveAs(const char* fileName) const;
        void setDefault(unsigned pageSize = DEF_PAGE_SIZE);
    public:
        TextFile(unsigned pageSize = DEF_PAGE_SIZE);
        TextFile(const char* filename, unsigned pageSize = DEF_PAGE_SIZE);
        TextFile(const TextFile& other);
        TextFile& operator=(const TextFile& other);
        ~TextFile();
        unsigned lines() const;
        const char* name() const;
        operator bool() const;
        const char* operator[](unsigned index) const;
        std::ostream& view(std::ostream& ostr) const;
        std::istream& getFile(std::istream& istr);
    };
    std::ostream& operator<<(std::ostream& ostr, const TextFile& text);
    std::istream& operator>>(std::istream& istr, TextFile& text);
}
#endif // !SENECA_TEXTFILE_H__
