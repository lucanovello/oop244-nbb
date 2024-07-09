#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "TextFile.h"
using namespace std;
namespace seneca {
	// LINE
	Line::Line() : m_value(nullptr) {}
	Line::~Line() {
		delete[] m_value;
	}
	Line::operator const char* () const {
		return m_value;
	}
	Line& Line::operator=(const char* lineContent) {
		delete[] m_value;
		if (lineContent) {
			m_value = new char[strlen(lineContent) + 1];
			strcpy(m_value, lineContent);
		}
		else {
			m_value = nullptr;
		}
		return *this;
	}

	void TextFile::setEmpty() {
		if (m_textLines) delete[] m_textLines;
		if (m_filename) delete[] m_filename;
		setDefault();
	}

	void TextFile::setFilename(const char* fname, bool isCopy) {
		delete[] m_filename;
		if (fname) {
			std::string prefix = isCopy ? "C_" : "";
			m_filename = new char[prefix.length() + strlen(fname) + 1];
			strcpy(m_filename, (prefix + fname).c_str());
		}
		else {
			m_filename = nullptr;
		}
	}

	void TextFile::setNoOfLines() {
		m_noOfLines = 0;
		if (m_filename) {
			std::ifstream file(m_filename);
			if (file.is_open()) {
				std::string line;
				while (std::getline(file, line)) {
					m_noOfLines++;
				}
				file.close();
				if (m_noOfLines == 0) {
					delete[] m_filename;
					m_filename = nullptr;
				}
			}
		}
	}

	void TextFile::loadText() {
		if (m_filename) {
			std::ifstream file(m_filename);
			setNoOfLines();
			delete[] m_textLines;
			m_textLines = new Line[m_noOfLines];
			std::string line;
			for (int i = 0; i < m_noOfLines && std::getline(file, line); ++i) {
				m_textLines[i] = line.c_str();
			}
			file.close();
		}
	}

	void TextFile::saveAs(const char* fileName) const {
		if (fileName) {
			std::ofstream file(fileName);
			if (file.is_open()) {
				for (int i = 0; i < m_noOfLines; ++i) {
					file << m_textLines[i] << '\n';
				}
				file.close();
			}
		}
	}

	void TextFile::setDefault(unsigned pageSize) {
		m_textLines = nullptr;
		m_filename = nullptr;
		m_noOfLines = 0;
		m_pageSize = pageSize;
	}

	TextFile::TextFile(unsigned pageSize) {
		setDefault();
	}

	TextFile::TextFile(const char* filename, unsigned pageSize) {
		setDefault();
		if (filename) {
			setFilename(filename);
			loadText();
		}
	}

	TextFile::TextFile(const TextFile& other)
	{
			*this = other;
	}

	TextFile& TextFile::operator=(const TextFile& other) {
		if (this != &other && other.m_filename) {
			setDefault();
			loadText();
			setFilename(other.m_filename, true);
			m_noOfLines = other.m_noOfLines;
			if (other.m_textLines && other.m_noOfLines > 0) {
				if (m_textLines) {
					delete[] m_textLines;
					m_textLines = nullptr;
				}
				m_textLines = new Line[m_noOfLines];
				for (size_t i = 0; i < m_noOfLines; ++i) {
					m_textLines[i] = 
						
						other.m_textLines[i];
				}
			}

		}
		return *this;
	}

	TextFile::~TextFile() {
		setEmpty();
	}

	unsigned TextFile::lines() const {
		return m_noOfLines;
	}

	const char* TextFile::name() const {
		return m_filename;
	}

	TextFile::operator bool() const {
		return m_filename != nullptr;
	}

	const char* TextFile::operator[](unsigned index) const {
		if (m_noOfLines == 0) return nullptr;
		return m_textLines[index % m_noOfLines];
	}

	std::ostream& TextFile::view(std::ostream& ostr) const {
		if (*this) {
			ostr << m_filename << '\n' << std::string(strlen(m_filename), '=') << '\n';
			for (int i = 0; i < m_noOfLines; ++i) {
				ostr << m_textLines[i] << '\n';
				if ((i + 1) % m_pageSize == 0 && i != m_noOfLines - 1) {
					ostr << "Hit ENTER to continue...";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
		return ostr;
	}

	std::istream& TextFile::getFile(std::istream& istr) {
		char filename[256];
		istr >> filename;
		setEmpty();
		setFilename(filename);
		loadText();
		return istr;
	}
	std::ostream& operator<<(std::ostream& ostr, const TextFile& text) {
		return text.view(ostr);
	}

	std::istream& operator>>(std::istream& istr, TextFile& text) {
		return text.getFile(istr);
	}
}