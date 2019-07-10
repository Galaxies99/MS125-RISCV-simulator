# include <vector>

# ifndef _PREDICTION_
  # define _PREDICTION_
  
class globalPrediction {
  private:
    std :: vector <int> cnt[60];
    int successCount, totalCount;
    double base[10];
    int mintimes[10];
    int callPrediction;
      
  public:
    globalPrediction() {
      callPrediction = 0;
      successCount = totalCount = 0;
      for (int i=0; i<60; ++i) cnt[i].clear();
      base[0] = 0.30, 
      base[1] = 0.40,
      base[2] = 0.50,
      base[3] = 0.60,
      base[4] = 0.73,
      base[5] = 0.8,
      base[6] = 0.85,
      base[7] = 0.87,
      base[8] = 0.89,
      base[9] = 0.91,
      base[10] = 0.93,
      base[11] = 0.95,
      base[12] = 0.97,
      base[13] = 0.99,
      base[14] = 1.0;
      mintimes[2] = 6;
      mintimes[3] = 5;
      mintimes[4] = 4;
      mintimes[5] = 4;
      mintimes[6] = 3;
      mintimes[7] = 3;
      mintimes[8] = mintimes[9] = 2;
    } 
    
    bool getPrediction(int i) {
      int length = cnt[i].size(), p[10], from;
      ++callPrediction; 
      if(callPrediction <= 50000) from = 6;
      else if(callPrediction <= 500000) from = 5;
      else from = 3;
      for (int len = from; len >= 2; -- len) {
        if(length < (len << 1)) continue;
        for (int j = 1; j <= len; ++j) p[j] = cnt[i][length - j];
        int cur = length - len, times = 0;
        while(cur >= len) {
          bool ok = 1;
          for (int j = 1; j <= len; ++j)
            if(p[j] != cnt[i][cur - j]) { ok = 0; break; }
          if(ok) {
            ++times;
            cur -= len;
          } else -- cur;
        }
        if(times > mintimes[len]) return p[len];
      }
      double cntt = 0;
      for (int j = length - 1; j >= 0 && j >= length - 15; --j)
        if(cnt[i][j]) cntt = cntt + base[j - length + 15];
        else cntt = cntt - base[j - length + 15];
      if(cntt < 0) return false;
      else return true;
    } 
    
    inline void addResult(int id, bool result, bool success) {
      if(cnt[id].size() < 30) cnt[id].push_back(result);
      else {
        for (int i=1; i<30; ++i) cnt[id][i-1] = cnt[id][i];
        cnt[id][29] = result;
      }
      if(success) ++ successCount;
      ++ totalCount;
    }
    
    inline void out() {
      cout << "Success " << successCount << " times, total " << totalCount << " times.\n";
      cout << "Accuracy: " << (double)successCount / totalCount * 100 << "%.\n";
    }
};

# endif
