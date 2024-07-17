#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "TextFile.h"
using namespace std;
namespace sdds {
	// LINE ----------------------------------------------------------
	Line::Line() : m_value(nullptr) {}

	Line::~Line() {
		delete[] m_value;
	}

	Line::operator const char* () const {
		return m_value;
	}

	Line& Line::operator=(const char* lineContent) {
		delete[] m_value;
		m_value = new char[strlen(lineContent) + 1];
		strcpy(m_value, lineContent);
		return *this;
	}

	// TEXTFILE ----------------------------------------------------------
    void TextFile::setFilename(const char* fname, bool isCopy) {
        delete[] m_filename;
        if (isCopy) {
            m_filename = new char[strlen("C_") + strlen(fname) + 1];
            strcpy(m_filename, "C_");
            strcat(m_filename, fname);
        }
        else {
            m_filename = new char[strlen(fname) + 1];
            strcpy(m_filename, fname);
        }
    }

    void TextFile::setNoOfLines() {
        ifstream file(m_filename);
        char ch;
        m_noOfLines = 0;
        while (file.get(ch)) {
            if (ch == '\n') {
                ++m_noOfLines;
            }
        }
        if (m_noOfLines > 0) {
            ++m_noOfLines;
        }
        else {
            delete[] m_filename;
            m_filename = nullptr;
            m_noOfLines = 0;
        }
    }

    void TextFile::loadText() {
        if (!m_filename) return;
        delete[] m_textLines;
        m_textLines = new Line[m_noOfLines];

        ifstream file(m_filename);
        string line;
        unsigned i = 0;
        while (getline(file, line)) {
            m_textLines[i] = line.c_str();
            ++i;
        }
        m_noOfLines = i;
    }

    void TextFile::saveAs(const char* fileName) const {
        ofstream file(fileName);
        for (unsigned i = 0; i < m_noOfLines; ++i) {
            file << (const char*)m_textLines[i] << endl;
        }
    }

    void TextFile::setEmpty() {
        delete[] m_textLines;
        m_textLines = nullptr;
        delete[] m_filename;
        m_filename = nullptr;
        m_noOfLines = 0;
    }

    TextFile::TextFile(unsigned pageSize) : m_textLines(nullptr), m_filename(nullptr), m_noOfLines(0), m_pageSize(pageSize) {}

    TextFile::TextFile(const char* filename, unsigned pageSize) : TextFile(pageSize) {
        if (filename) {
            setFilename(filename);
            setNoOfLines();
            loadText();
        }
    }

    TextFile::TextFile(const TextFile& src) : TextFile(src.m_pageSize) {
        if (src) {
            setFilename(src.m_filename, true);
            src.saveAs(m_filename);
            setNoOfLines();
            loadText();
        }
    }

    TextFile& TextFile::operator=(const TextFile& src)
    {
        if (this != &src) {
            if (m_textLines != nullptr) {
                delete[] m_textLines;
                m_textLines = nullptr;
            }
            if (src.m_textLines && src.m_noOfLines > 0) {
                this->m_noOfLines = src.m_noOfLines;
                m_textLines = new Line[m_noOfLines];
                for (unsigned i = 0; i < m_noOfLines; i++) {
                    m_textLines[i].m_value = new char[strlen(src.m_textLines[i].m_value) + 1];
                    strcpy(m_textLines[i].m_value, src.m_textLines[i].m_value);
                }
                saveAs(m_filename);
            }
        }
        return *this;
    }

    TextFile::~TextFile() {
        setEmpty();
    }

    std::ostream& TextFile::view(std::ostream& ostr) const {
        if (*this) {
            ostr << m_filename << endl;
            ostr << string(strlen(m_filename), '=') << endl;
            for (unsigned i = 0; i < m_noOfLines; ++i) {
                ostr << (const char*)m_textLines[i] << endl;
                if ((i + 1) % m_pageSize == 0) {
                    ostr << "Hit ENTER to continue...";
                    cin.get();
                }
            }
        }
        return ostr;
    }

    std::istream& TextFile::getFile(std::istream& istr) {
        string filename;
        istr >> filename;
        setEmpty();
        setFilename(filename.c_str());
        setNoOfLines();
        loadText();
        return istr;
    }

    TextFile::operator bool() const {
        return m_filename != nullptr;
    }

    unsigned TextFile::lines() const {
        return m_noOfLines;
    }

    const char* TextFile::name() const {
        return m_filename;
    }

    const char* TextFile::operator[](unsigned index) const {
        return m_textLines[index % m_noOfLines];
    }

    std::ostream& operator<<(std::ostream& ostr, const TextFile& text) {
        return text.view(ostr);
    }

    std::istream& operator>>(std::istream& istr, TextFile& text) {
        return text.getFile(istr);
    }

}
