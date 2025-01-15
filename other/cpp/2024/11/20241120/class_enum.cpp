#include <bits/stdc++.h>

class Report {
 public:
  enum MonitorIndex {
    kMonitorBegin = 0,
    kMiniVersionUpdateTotal,
    kMiniVersionUpdateElapse,
    kMonitorEnd,
  };

 public:
};

int main() {
  printf("kMonitorBegin=%d\n", int(Report::kMonitorBegin));
  printf("kMiniVersionUpdateTotal=%d\n", int(Report::kMiniVersionUpdateTotal));
  printf("kMiniVersionUpdateElapse=%d\n", int(Report::kMiniVersionUpdateElapse));
  return 0;
}
