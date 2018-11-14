template <typename Object>
class Vector {
        public:
                explicit Vector(int init_size = 0) {
                        size = init_size;
                        capacity = init_size + SPACE_CAPACITY;
                        objects = new Object[capacity];
                }

                Vector(const Vector& rhs) {
                        size = rhs.size;
                        capacity = rhs.capacity;
                        objects = nullptr;

                        objects = new Object[capacity];
                        for(int i = 0; i < size; ++i) {
                                objects[i] = rhs.objects[i];
                        }
                }

                Vector& operator=(const Vector& rhs) {
                        Vector copy = rhs;
                        std::swap(*this, copy);
                        return *this;
                }

                ~Vector() {
                        delete [] objects;
                }

                Vector(Vector&& rhs) {
                        size = rhs.size;
                        capacity = rhs.capacity;
                        objects = rhs.objects;

                        rhs.objects = nullptr;
                        rhs.size = 0;
                        rhs.capacity = 0;
                }

                Vector& operator= (Vector&& rhs) {
                        std::swap(size, rhs.size);
                        std::swap(capacity, rhs.capacity);
                        std::swap(objects, rhs.objects);

                        return *this;
                }

                void resize(int new_size) {
                        if(new_size > capacity) {
                                reserve(capacity);
                                size = new_size;
                        }
                }

                void reserve(int new_capacity) {
                        if(new_capacity < size) {
                                return;
                        }

                        // create a reserve array and move all objects
                        // of current array into it.
                        Object* new_array = new Object[new_capacity];
                        for(int i = 0; i < size; ++i) {
                                new_array[i] = std::move(objects[i]);
                        }


                        capacity = new_capacity;

                        // the current object storage is the reserve array.
                        std::swap(objects, new_array);

                        // delete the reserve array.
                        delete [] new_array;
                }

                Object& operator[](int index) {
                        return objects[index];
                }

                const Object& operator[](int index) const {
                        return objects[index];
                }

                bool empty() const {
                        return size() == 0;
                }

                int size() const {
                        return size;
                }

                int capacity() const {
                        return capacity;
                }

                void push_back(const Object& x) {
                        if(size == capacity) {
                                reserve(2 * capacity + 1);
                        }

                        objects[size++] = x;
                }

                void pop_back() {
                        return --size;
                }

                const Object& back() const {
                        return objects[size-1];
                }

                typedef Object* iterator;
                typedef const Object* const_iterator;

                iterator begin() {
                        return &object[0];
                }

                const_iterator begin() const {
                        return &objects[0];
                }

                iterator end() {
                        return &objects[size()];
                }

                const_iterator end() const {
                        return &objects[size()]
                }

                static const int SPACE_CAPACITY = 16;

        private:
                int size;
                int capacity;
                Object *objects;
};
