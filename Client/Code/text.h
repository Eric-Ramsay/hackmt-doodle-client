#pragma once

template <typename Type> std::string to_str(const Type& t) {
	std::ostringstream os;
	os << t;
	return os.str();
}


std::string operator+(std::string str, int num)
{
	return str + to_str(num);
}

std::string operator+(int num, std::string str)
{
	return str + to_str(num);
}

bool endsWith(std::string stringOne, std::string stringTwo) {
	if (stringOne.size() < stringTwo.size()) {
		return false;
	}
	for (int i = 0; i < stringTwo.size(); i++) {
		if (stringOne[(stringOne.size() - stringTwo.size()) + i] != stringTwo[i]) {
			return false;
		}
	}
	return true;
}

bool includes(std::string stringOne, std::string stringTwo) {
	return stringOne.find(stringTwo) != std::string::npos;
}

std::vector<std::string> split(std::string str, char delim = ' ') {
	std::vector<std::string> strings = { "" };
	for (int i = 0; i < str.size(); i++) {
		char c = str[i];
		if (c == delim) {
			if (i < str.size() - 1) {
				strings.push_back("");
			}
		}
		else {
			strings[strings.size() - 1] += c;
		}
	}
	return strings;
}

std::string join(std::vector<std::string> words, char delim = ' ') {
	std::string text = "";
	for (int i = 0; i < words.size(); i++) {
		text += words[i];
		if (i < words.size() - 1) {
			text += delim;
		}
	}
	return text;
}

std::string low(std::string a) {
	std::string word = "";
	for (char c : a) {
		if (c >= 'A' && c <= 'Z') {
			word += (c - 'A') + 'a';
		}
		else {
			word += c;
		}
	}
	return word;
}

std::string caps(std::string a) {
	std::string word = "";
	for (char c : a) {
		if (c >= 'a' && c <= 'z') {
			word += (c - 'a') + 'A';
		}
		else {
			word += c;
		}
	}
	return word;
}

std::string replace(std::string str, std::string findText, std::string replaceText) {
	std::string newStr = "";
	int len = findText.length();
	int strLen = str.length();
	for (int i = 0; i < strLen; i += len) {
		std::string segment = "";
		for (int j = 0; j < len; j++) {
			if (i + j < strLen) {
				segment += str[i + j];
			}
		}
		if (segment == findText) {
			segment = replaceText;
		}
		newStr += segment;
	}
	str = newStr;
	return str;
}