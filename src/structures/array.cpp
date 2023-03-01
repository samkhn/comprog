// Demo of (dynamically allocated) arrays

#include <cstdint>
#include <cstdio>
#include <memory>
#include <string>
#include <unordered_map>

struct StatusOrInt32 {
  int32_t status;
  int32_t value;
};

class Vector {
public:
  Vector() {
    size_ = 0;
    capacity_ = 8;
    array_ = (int32_t *)malloc(capacity_ * sizeof(int32_t));
  }

  void Resize(uint32_t new_size) {
    printf("Resizing from %d to %d\n", capacity_, new_size);
    capacity_ = new_size;
    int32_t *new_array = (int32_t *)malloc(capacity_ * sizeof(int32_t));
    for (uint32_t i = 0; i < size_; ++i) {
      new_array[i] = array_[i];
    }
    int32_t *old = array_;
    array_ = new_array;
    free(old);
  }

  void Resize() {
    // TODO: Is this multiply and cast okay?
    Resize((uint32_t)capacity_ * 1.25);
  }

  void Push(int32_t v) {
    if (size_ == capacity_) {
      Resize();
    }
    array_[size_++] = v;
  }

  void Push(std::initializer_list<int32_t> vs) {
    for (const int32_t &v : vs) {
      Push(v);
    }
  }

  StatusOrInt32 At(uint32_t i) const {
    if (!size_ || i > size_) {
      return {-1, 0};
    }
    return {0, array_[i]};
  };

  uint32_t Size() const { return size_; };

  void RotateRightBy(uint32_t by) {
    while (by != 0) {
      RotateRight(/*discard?=*/false);
      by--;
    }
  }

  void RotateLeftBy(uint32_t by) {
    while (by != 0) {
      RotateLeft(/*discard?=*/false);
      by--;
    }
  }

  void ShiftRightBy(uint32_t by) {
    while (by != 0) {
      RotateRight(/*discard?=*/true);
      by--;
    }
  }
  void ShiftLeftBy(uint32_t by) {
    while (by != 0) {
      RotateLeft(/*discard?=*/true);
      by--;
    }
  }

  void RotateRight() { RotateRightBy(1); }
  void RotateLeft() { RotateLeftBy(1); }
  void ShiftRight() { ShiftRightBy(1); }
  void ShiftLeft() { ShiftLeftBy(1); }

  std::string ToString() const {
    if (size_ == 0) {
      return "";
    }
    uint32_t i = 0;
    std::string s = std::to_string(array_[i++]);
    for (; i < size_; ++i) {
      s.append(" ");
      s.append(std::to_string(array_[i]));
    }
    return s;
  }

private:
  int32_t *array_;
  uint32_t size_;
  uint32_t capacity_;

  void RotateRight(bool discard) {
    if (!size_) {
      return;
    }
    int32_t v = array_[size_ - 1];
    for (uint32_t i = size_; i > 0; --i) {
      array_[i] = array_[i - 1];
    }
    if (discard) {
      array_[0] = 0;
    } else {
      array_[0] = v;
    }
  }

  void RotateLeft(bool discard) {
    if (!size_) {
      return;
    }
    int32_t v = array_[0];
    for (uint32_t i = 0; i < size_; ++i) {
      array_[i] = array_[i + 1];
    }
    if (discard) {
      array_[size_] = 0;
    } else {
      array_[size_] = v;
    }
  }
};

Vector PrefixSum(const Vector &v) {
  Vector ps;
  int sum = 0;
  StatusOrInt32 s_or_v;
  for (uint32_t i = 0; i < v.Size(); ++i) {
    s_or_v = v.At(i);
    if (s_or_v.status != 0) {
      printf("Error: v.At(%d) returned error. Stopping PrefixSum.\n", i);
      return Vector();
    }
    sum += s_or_v.value;
    ps.Push(sum);
  }
  return ps;
}

using Histogram = std::unordered_map<int32_t, uint32_t>;

Histogram ToHistogram(const Vector &v) {
  Histogram h;
  StatusOrInt32 s_or_v;
  for (uint32_t i = 0; i < v.Size(); ++i) {
    s_or_v = v.At(i);
    if (s_or_v.status != 0) {
      printf("Error: v.At(%d) returned error. Stopping PrefixSum.\n", i);
      return {};
    }
    h[s_or_v.value] = h[s_or_v.value] + 1;
  }
  return h;
}

std::string Print(const Histogram &h) {
  std::string s = "";
  for (auto &kv : h) {
    s.append("Value ");
    s.append(std::to_string(kv.first));
    s.append(" was observed ");
    s.append(std::to_string(kv.second));
    s.append(" times\n");
  }
  return s;
}

int main() {
  Vector v;
  printf("Empty vector: %s\n", v.ToString().c_str());
  v.Push(1);
  printf("v.Push(1). v is now %s\n", v.ToString().c_str());
  v.Push({3, 2, -1, 0});
  printf("v.Push({3, 2, -1, 0}). v is now %s\n", v.ToString().c_str());
  printf("PrefixSum(v). Got {%s}. Want {1 4 6 5 5}\n",
         PrefixSum(v).ToString().c_str());
  v.Push({1, 3, 5, 6, 8, 10});
  printf("v.Push({1, 3, 5, 6, 8, 10}). v is now %s\n", v.ToString().c_str());
  Vector a;
  a.Push({1, 1, 2, 2, 2, 3});
  printf("In {%s}\n%s", a.ToString().c_str(), Print(ToHistogram(a)).c_str());
  a.RotateRightBy(1);
  printf("a, rotated right, is %s\n", a.ToString().c_str());
  a.RotateLeftBy(1);
  printf("then, rotated left, is %s\n", a.ToString().c_str());
  a.ShiftRightBy(1);
  printf("a, shifted right, is %s\n", a.ToString().c_str());
  return 0;
}
