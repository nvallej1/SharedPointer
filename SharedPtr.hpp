#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP

#include <utility>
#include <iostream>

namespace cs540 {
	/* Smart pointer with ref counter*/
	template <typename T>
    class SharedPtr {
    private:
        class RC {
            int ref_count {0};
        public:
            void increment() { ++ref_count; }
            void decrement() { if(ref_count > 0) --ref_count; }
            bool isEmpty()  { return ref_count == 0; }
            void set(int rc) { ref_count = rc; }
            int get() { return ref_count; }
        };
        T * raw_ptr;
        RC * m_rc;
    public:
        SharedPtr();
        SharedPtr(SharedPtr<T> &&p);
        SharedPtr(const SharedPtr<T> &p);
        template <typename U> SharedPtr(SharedPtr<U> &&p);
        template <typename U> SharedPtr(const SharedPtr<U> &p);
        template <typename U> explicit SharedPtr(U * p);
        ~SharedPtr();

        SharedPtr<T> &operator=(const SharedPtr<T> &other);
        template <typename U> SharedPtr<T> &operator=(const SharedPtr<U> &other);
        SharedPtr<T> &operator=(SharedPtr<T> &&p);
        template <typename U> SharedPtr<T> &operator=(SharedPtr<U> &&p);

        void reset();
        template <typename U> void reset(U *p);

        T *get() const;
        T &operator*() const;
        T *operator->() const;
        explicit operator bool() const;
        RC *get_rc() const;
    };

	template <typename T>
	SharedPtr<T>::SharedPtr() {
		raw_ptr = nullptr;
	}

    template <typename T>
    SharedPtr<T>::SharedPtr(SharedPtr<T> &&p) {
        this->raw_ptr = std::move(p.get());
        m_rc->increment();
    }

	template <typename T>
	SharedPtr<T>::SharedPtr(const SharedPtr<T> &p) {
		this->raw_ptr = p.get();
		m_rc->increment();
	}

    template <typename T>
	template <typename U>
    SharedPtr<T>::SharedPtr(SharedPtr<U> &&p) {
        this->raw_ptr = std::move(dynamic_cast<T*>(p.get()));
        m_rc->increment();
    }

	template <typename T>
	template <typename U>
	SharedPtr<T>::SharedPtr(const SharedPtr<U> &p) {
		this->raw_ptr = static_cast<T*>(p.get());
		m_rc->increment();
	}

    template <typename T>
    template <typename U>
    SharedPtr<T>::SharedPtr(U * p) {
        this->raw_ptr = static_cast<T*>(p);
        m_rc->increment();
    }

	template <typename T>
	SharedPtr<T>::~SharedPtr() {
		m_rc->decrement();
		if (m_rc->isEmpty())
			delete raw_ptr;
	}

    template <typename T>
    SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T> &other) {
        this->m_rc->decrement();
        this->raw_ptr = other.get();
        this->m_rc->set(other.get_rc()->get());
        this->m_rc->increment();
        return *this;
    }

    template <typename T>
    template <typename U>
    SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<U> &other) {
        this->m_rc->decrement();
        this->raw_ptr = dynamic_cast<T*>(other.get());
        this->m_rc->set(other.get_rc()->get());
        this->m_rc->increment();
        return *this;
    }

    template <typename T>
    SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T> &&p) {
        this->m_rc->decrement();
        this->raw_ptr = std::move(p.get());
        this->m_rc->set(p.get_rc()->get());
        this->m_rc->increment();
        return *this;
    }

    template <typename T>
    template <typename U>
    SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<U> &&p) {
        this->m_rc->decrement();
        this->raw_ptr = std::move(dynamic_cast<T*>(p.get()));
        this->m_rc->set(p.get_rc()->get());
        this->m_rc->increment();
        return *this;
    }

    template <typename T>
    void SharedPtr<T>::reset() {
        this->raw_ptr = nullptr;
        this->m_rc->decrement();
    }

    template <typename T>
    template <typename U>
    void SharedPtr<T>::reset(U *p) {
        if (this->m_rc->isEmpty()) {
            delete this;
        } else {
            this->raw_ptr = static_cast<T*>(p);
        }
    }

    template <typename T>
    T * SharedPtr<T>::get() const {
        return raw_ptr;
    }

    template <typename T>
    T & SharedPtr<T>::operator*() const {
        return *raw_ptr;
    }

    template <typename T>
    T * SharedPtr<T>::operator->() const {
        return raw_ptr;
    }

    template <typename T>
    SharedPtr<T>::operator bool() const {
        return raw_ptr != nullptr;
    }

    template <typename T>
    typename SharedPtr<T>::RC * SharedPtr<T>::get_rc() const {
        return m_rc;
    }

    // Free Functions =================================================

    template <typename T1, typename T2>
    bool operator==(const SharedPtr<T1> &sp1, const SharedPtr<T2> &sp2) {
        return (sp1.get() == sp2.get()
            || (sp1.get() == nullptr && sp2.get() == nullptr));
    }

    template <typename T>
    bool operator==(const SharedPtr<T> &sp, std::nullptr_t) {
        return sp.get() == nullptr;
    }

    template <typename T>
    bool operator==(std::nullptr_t, const SharedPtr<T> &sp) {
        return sp.get() == nullptr;
    }

    template <typename T1, typename T2>
    bool operator!=(const SharedPtr<T1>&sp1, const SharedPtr<T2> &sp2) {
        return (sp1.get() == sp2.get()
            || (sp1.get() == nullptr && sp2.get() != nullptr)
            || (sp1.get() != nullptr && sp2.get() == nullptr));
    }

    template <typename T>
    bool operator!=(const SharedPtr<T> &sp, std::nullptr_t) {
        return sp.get() != nullptr;
    }

    template <typename T>
    bool operator!=(std::nullptr_t, const SharedPtr<T> &sp) {
        return sp.get() != nullptr;
    }

    template <typename T, typename U> SharedPtr<T>
    static_pointer_cast(const SharedPtr<U> &sp) {
        static_cast<T*>(sp.get());
        return sp;
    }

    template <typename T, typename U>
    SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U> &sp) {
        dynamic_cast<T*>(sp.get());
        return sp;
    }
}

#endif
