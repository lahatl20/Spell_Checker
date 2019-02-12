
        template<class HashedObj>
        Dictionary<HashedObj>::Dictionary(const HashedObj & notFound, int size) 
        : items(notFound, size)
	      {}

        template<class HashedObj>
        void Dictionary<HashedObj>::insert(const HashedObj & key)
        {
                        // INSERT ONE LINE
                       items.insert(key);
        }

        template<class HashedObj>
	const HashedObj & Dictionary<HashedObj>::lookup (const HashedObj & key) const
	{
                        // INSERT ONE LINE
                        items.find(key);
	}

        template<class HashedObj>
	void Dictionary<HashedObj>::makeEmpty()
	{
                        // INSERT ONE LINE
                        items.makeEmpty();
	}