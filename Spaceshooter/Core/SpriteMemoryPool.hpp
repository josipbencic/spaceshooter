#ifndef SPRITEMEMORYPOOL_HPP
#define SPRITEMEMORYPOOL_HPP

#include <cstring>  // memset
#include <cassert>  // assert
#include <new>      // placement new

namespace loop_tools {

  /*
    This is a class used for memory storage.

    Number of Sprites of a single type
    will not get above 30000 in this game,
    so short will be used for indexing.

    TODO: Augment this to linked list with indices as links.
  */

  template <typename Sprite>
  class SpriteMemoryPool {
  public:

    class iterator;
    class const_iterator;

    SpriteMemoryPool(short size = 8)
      : data_(0)
      , capacity_(size)
      , end_(0) {
    
      data_ = reinterpret_cast<Sprite*>(
        new char[capacity_ * sizeof(Sprite)]);
      assert(data_);
    }

    void clear() {
      for (short i = 0; i < end_; i++) {
        data_[i].~Sprite();
      }
      end_ = 0;
    }

    ~SpriteMemoryPool() {
      clear();
      delete[] reinterpret_cast<char*>(data_);
    }

    inline short size() const {
      return end_;
    }

    inline short max_size() const {
      return capacity_;
    }

    inline void insert(const Sprite& x) {

      Sprite* tmp = new(data_ + end_) Sprite(x);
      end_++;

      if (end_ == capacity_) {
        expand();
      }
    }

    void expand() {
      capacity_ = capacity_ * 2;
      Sprite* tmp = reinterpret_cast<Sprite*>(
        new char[capacity_ * sizeof(Sprite)]);

      for (short i = 0; i < end_; i++) {
        Sprite* create = new (tmp + i) Sprite(data_[i]);
      }
      short tmp_end = end_;

      clear();
      delete[] reinterpret_cast<char*>(data_);
      data_ = tmp;
      end_ = tmp_end;
    }

    iterator remove(const iterator& it) {

      assert (it.index_ < capacity_ && it.index_ > -1);

      for (short i = it.index_; i < end_ - 1; i++) {
        data_[i].~Sprite();
        memset(data_ + i, 0, sizeof(Sprite));
        Sprite* create = new (data_ + i) Sprite(data_[i + 1]);
      }
      data_[end_ - 1].~Sprite();
      memset(data_ + end_ - 1, 0, sizeof(Sprite));
      end_--;

      return iterator(data_, it.index_);
    }
  
    class iterator {

      friend class SpriteMemoryPool<Sprite>;

      friend Sprite& operator* (const iterator& it) {
        assert (it.index_ > -1);
        return *(it.ptr_ + it.index_);
      }

    public:
      bool operator!= (const iterator& rhs) {
        return index_ != rhs.index_;
      }

      const iterator& operator++() {
        index_++;
        return *this;
      }

      iterator operator++(int) {
        iterator result = *this;
        ++(*this);
        return result;
      }

    private:
      iterator(Sprite* ptr, short index = 0)
        : ptr_(ptr), index_(index)
      {}

      Sprite* ptr_;
      short index_;
    };

    class const_iterator {

      friend class SpriteMemoryPool<Sprite>;

      friend const Sprite& operator* (const const_iterator& it) {
        assert (it.index_ > -1);
        return *(it.ptr_ + it.index_);
      }

    public:
      bool operator!= (const const_iterator& rhs) {
        return index_ != rhs.index_;
      }

      const const_iterator& operator++() {
        index_++;
        return *this;
      }

      const_iterator operator++(int) {
        const_iterator result = *this;
        ++(*this);
        return result;
      }

    private:
    
      const_iterator(Sprite* ptr, short index = 0)
        : ptr_(ptr), index_(index)
      {}
    
      Sprite* ptr_;
      short index_;
    };

    inline iterator begin() const {
      return iterator(data_);
    }

    inline iterator end() const {
      return iterator(data_, end_);
    }

    inline const_iterator cbegin() const {
      return const_iterator(data_);
    }

    inline const_iterator cend() const {
      return const_iterator(data_, end_);
    }

  private:
    Sprite* data_;
    short   capacity_;
    short   end_;
  
    /*
      Copying or assigning won't be allowed.
    */
    SpriteMemoryPool(const SpriteMemoryPool&) {}
    const SpriteMemoryPool& operator= (const SpriteMemoryPool&) {}
  };
}

#endif
