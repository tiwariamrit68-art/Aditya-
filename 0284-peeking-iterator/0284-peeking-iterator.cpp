/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *  public:
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

class PeekingIterator : public Iterator {
private:
    int nextElement;
    bool hasNextElement;

public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {
        hasNextElement = Iterator::hasNext();

        if (hasNextElement) {
            nextElement = Iterator::next();
        }
    }

    // Returns the next element without moving the pointer
    int peek() {
        return nextElement;
    }

    // Returns the next element and moves forward
    int next() {
        int current = nextElement;

        hasNextElement = Iterator::hasNext();

        if (hasNextElement) {
            nextElement = Iterator::next();
        }

        return current;
    }

    bool hasNext() const {
        return hasNextElement;
    }
};