#include <bits/stdc++.h>
using namespace std;
enum class CleanupReason {
  kNone,  // Placeholder, not actually used.
  kHandshakeFailed,
  kDisconnect,
  UserInitiated,
  kClosing,
  kError
};
int main() {
  printf("CleanupReason=%d\n", sizeof(CleanupReason));
  return 0;
}