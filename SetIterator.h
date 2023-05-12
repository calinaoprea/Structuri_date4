#pragma once
#include "Set.h"

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:
	//DO NOT CHANGE THIS PART
    struct Node {
        TElem info;
        bool deleted;

        Node() : info(NULL_TELEM), deleted(false) {}
    };
	const Set& set;
	SetIterator(const Set& s);
    Node* currentNode;
    int currentPos;

	//TODO - Representation

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};


