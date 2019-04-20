#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP

namespace cs540 {
	/* Smart pointer with ref counter*/
	template <typename T>
	class SharedPtr {
	private:
		class RC {
			int ref_count {0};
		public:
			void increment() { ++ref_count; }
			void decrement() { ++ref_count; }
			bool isEmpty()  { return ref_count == 0; }
		};
		T * ptr;
		RC m_rc;
	public:
		SharedPtr();
		SharedPtr(const SharedPtr<T> &p);
		template <typename U> explicit SharedPtr(U * p);
		template <typename U> SharedPtr(const SharedPtr<U> &p);
		~SharedPtr();
	};

	template <typename T>
	SharedPtr<T>::SharedPtr() {
		ptr = nullptr;
	}

	template <typename T>
	SharedPtr<T>::SharedPtr(const SharedPtr<T> &p) {
		ptr = &p;
		m_rc.increment();
	}

	template <typename T>
	template <typename U>
	SharedPtr<T>::SharedPtr(U * p) {
		ptr = new U(*p);
		m_rc.increment();
	}

	template <typename T>
	template <typename U>
	SharedPtr<T>::SharedPtr(const SharedPtr<U> &p) {
		ptr = &p;
		m_rc.increment();
	}

	template <typename T>
	SharedPtr<T>::~SharedPtr() {
		m_rc.decrement();
		if (m_rc.isEmpty())
			delete ptr;
	}

}

#endif
