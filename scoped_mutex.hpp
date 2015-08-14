/***********************************************************************
 * Author :          dingchangjiang
 * Email :           dcj227@163.com
 * Last modified :   2015-08-13 23:32
 * Filename :        scoped_mutex.hpp
 * Description :     
 * *********************************************************************/

#include <pthread.h>

#include <assert.h>

namespace dcj {

class Mutex {
 public:
  Mutex() {
    pthread_mutex_init(&mutex_, NULL);
  }

  ~Mutex() {
    pthread_mutex_destroy(&mutex_);
  }

  int Lock() {
    if (pthread_mutex_lock(&mutex_) != 0) {
      return -1;
    }
    return 0;
  }

  int TryLock() {
    if (pthread_mutex_trylock(&mutex_) != 0) {
      return -1;
    }
    return 0;
  }

  int Unlock() {
    if (pthread_mutex_unlock(&mutex_) != 0) {
      return -1;
    }
    return 0;
  }

 private:
  Mutex(const Mutex& m);
  Mutex& operator=(const Mutex& m);

  pthread_mutex_t mutex_;
};

class ScopedMutex {
 public:
  ScopedMutex(Mutex* pmutex) {
    assert(pmutex);
    pmutex_ = pmutex;
    pmutex_->Lock();
  }

  ~ScopedMutex() {
    pmutex_->Unlock(); 
  }

 private:
  Mutex* pmutex_;
};

class ScopedTryMutex {
 public:
  ScopedTryMutex(Mutex* pmutex) {
    assert(pmutex);
    pmutex_ = pmutex;
    pmutex_->TryLock();
  }

  ~ScopedTryMutex() {
    pmutex_->Unlock();
  }

 private:
  Mutex* pmutex_;
};

} // namespace dcj
