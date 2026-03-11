#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    int N = 2, M = 0;
    
    vector<vector<int>> bad_up(N + 2, vector<int>(N + 2, 0));
    vector<vector<int>> bad_dn(N + 2, vector<int>(N + 2, 0));
    
    vector<vector<int>> preUp(N + 2, vector<int>(N + 2, 0));
    vector<vector<int>> preDn(N + 2, vector<int>(N + 2, 0));
    for (int r = 1; r <= N; r++) {
        for (int j = 1; j <= N; j++) {
            preUp[r][j] = preUp[r][j - 1] + bad_up[r][j];
            preDn[r][j] = preDn[r][j - 1] + bad_dn[r][j];
        }
    }

    auto queryUp = [&](int row, int l, int r) -> bool {
        if (l > r || r <= 0) return false;
        r = min(r, N);
        return (preUp[row][r] - preUp[row][l - 1]) > 0;
    };
    auto queryDn = [&](int row, int l, int r) -> bool {
        if (l > r || r <= 0) return false;
        r = min(r, N);
        return (preDn[row][r] - preDn[row][l - 1]) > 0;
    };

    vector<vector<int>> maxK(N + 2, vector<int>(N + 2, 0));
    for (int r = 1; r <= N; r++) {
        for (int j = 1; j <= r; j++) {
            if (bad_up[r][j]) continue;
            maxK[r][j] = 1;
            for (int k = 2; r + k - 1 <= N; k++) {
                int bot = r + k - 1;
                if (queryUp(bot, j, j + k - 1) || queryDn(bot, j, j + k - 2)) break;
                maxK[r][j] = k;
            }
        }
    }
    
    printf("maxK:\n");
    for (int r = 1; r <= N; r++) {
        for (int j = 1; j <= r; j++) {
            printf("  maxK[%d][%d]=%d\n", r, j, maxK[r][j]);
        }
    }
    
    // 方向1
    vector<int> tmpU(N + 2, 0), tmpD(N + 2, 0);
    for (int r = 1; r <= N; r++) {
        for (int j = 1; j <= r; j++) {
            int k = maxK[r][j];
            if (k <= 0) continue;
            for (int kk = 1; kk <= k; kk++) {
                tmpU[r + kk - 1] = max(tmpU[r + kk - 1], kk * kk);
                tmpD[r] = max(tmpD[r], kk * kk);
            }
        }
    }
    
    printf("tmpU: "); for (int i=0;i<=N+1;i++) printf("%d ", tmpU[i]); printf("\n");
    printf("tmpD: "); for (int i=0;i<=N+1;i++) printf("%d ", tmpD[i]); printf("\n");
    
    vector<int> maxUp(N + 2, 0), maxDn(N + 2, 0);
    for (int r = 1; r <= N; r++) maxUp[r] = max(maxUp[r - 1], tmpU[r]);
    for (int r = N; r >= 1; r--) maxDn[r] = max(maxDn[r + 1], tmpD[r]);
    
    printf("maxUp: "); for (int i=0;i<=N+1;i++) printf("%d ", maxUp[i]); printf("\n");
    printf("maxDn: "); for (int i=0;i<=N+1;i++) printf("%d ", maxDn[i]); printf("\n");
    
    int ans = 0;
    for (int cut = 0; cut <= N; cut++) {
        printf("cut=%d: maxUp=%d maxDn=%d sum=%d\n", cut, maxUp[cut], maxDn[cut+1], maxUp[cut]+maxDn[cut+1]);
        ans = max(ans, maxUp[cut] + maxDn[cut + 1]);
    }
    printf("ans=%d\n", ans);
    return 0;
}
