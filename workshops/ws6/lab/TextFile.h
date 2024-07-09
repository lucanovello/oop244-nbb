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
        operator const char* ()const;
        Line& operator=(const char* lineContent);
        friend class TextFile;
        Line(const Line&) = delete;
        Line& operator=(const Line&) = delete;
   };
   // TEXTFILE ------------------------------------------
    class TextFile {
        Line* m_textLines;
        char* m_filename;
        unsigned m_noOfLines;
        unsigned m_pageSize;

        void setFilename(const char* fname, bool isCopy = false);
        void setNoOfLines();
        void loadText();
        void saveAs(const char* fileName)const;
        void setEmpty();
        void setDefault(unsigned pageSize = DEF_PAGE_SIZE);
    public:
        TextFile(unsigned pageSize = 15);
        TextFile(const char* filename, unsigned pageSize = 15);
        TextFile(const TextFile&);
        TextFile& operator=(const TextFile&);
        ~TextFile();
        std::ostream& view(std::ostream& ostr)const;
        std::istream& getFile(std::istream& istr);
        operator bool()const;
        unsigned lines()const;
        const char* name()const;
        const char* operator[](unsigned index)const;
    };

    std::ostream& operator<<(std::ostream& ostr, const TextFile& text);
    std::istream& operator>>(std::istream& istr, TextFile& text);
}
#endif // !SENECA_TEXTFILE_H__
