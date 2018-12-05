

////////////////////////////////////////////////////////////
inline bool af::XML::Structure::operator==(const Structure & right)
{
	if (right.key != key)
		return false;
	if (right.content != content)
		return false;
	if (right.attributes.size() != attributes.size())
		return false;
	if (!right.attributes.empty()) {
		if (attributes != right.attributes) return false;
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
