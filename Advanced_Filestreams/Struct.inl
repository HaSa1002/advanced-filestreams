inline bool af::XML::Attribute::operator==(const Attribute & right)
{
	if (right.name != name)
		return false;
	if (right.content != content)
		return false;
	return true;
}

inline bool af::XML::Attribute::operator!=(const Attribute & right)
{
	if (right.name == name)
		return false;
	if (right.content == content)
		return false;
	return true;
}


inline bool af::XML::Structure::operator==(const Structure & right)
{
	if (right.key != key)
		return false;
	if (right.content != content)
		return false;
	if (right.attributes.size() != attributes.size())
		return false;
	if (!right.attributes.empty()) {
		for (unsigned int i = 0; i < attributes.size(); ++i) {
			Attribute l = attributes.at(i);
			Attribute r = right.attributes.at(i);
			if (l != r)
				return false;
		}
	}
	if (right.childs.size() != childs.size())
		return false;
	if (!right.childs.empty()) {
		for (unsigned int i = 0; i < childs.size(); ++i) {
			if (!childs.at(i).operator==(right.childs.at(i)))
				return false;
		}
	}
	return true;
}
