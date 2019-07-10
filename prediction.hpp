# include <deque>

# ifndef _PREDICTION_
  # define _PREDICTION_
  
class globalPrediction {
  private:
    std :: deque <int> cnt[60];
    int successCount, totalCount;
    double base[10];
      
  public:
    globalPrediction() {
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
    } 
    
    bool getPrediction(int i) {
      int length = cnt[i].size(), times;
      if(length > 6) {
        times = 0;
        for (int j = length - 1; j >= 2; j -= 3)
          if(cnt[i][j] == cnt[i][length - 1] && cnt[i][j-1] == cnt[i][length - 2] && cnt[i][j-2] == cnt[i][length - 3]) ++times;
        if(times > 5) return cnt[i][length - 3];
        
        times = 0;
        for (int j = length - 1; j >= 1; j -= 2) 
          if(cnt[i][j] == cnt[i][length - 1] && cnt[i][j-1] == cnt[i][length - 2]) ++times;
        if(times > 5) return cnt[i][length - 2];
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
        cnt[id].pop_front();
        cnt[id].push_back(result);
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
