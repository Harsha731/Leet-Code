// https://discuss.leetcode.com/topic/46904/very-concise-c-solution
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
*/

// getIntervals : O(N)
// addNumber : O(logN)

class SummaryRanges {
private:
    set<int> nums;
    
public:
    SummaryRanges() {}

    void addNum(int val) {
        nums.insert(val);
    }

    vector<vector<int>> getIntervals() {
        vector<vector<int>> res;
        if (nums.empty()) return res;

        int s = *nums.begin();
        int e = s;

        for (auto it = ++nums.begin(); it != nums.end(); ++it) {    
            // starting from the 2nd element, so ++nums.begin() is present
            if (*it == e + 1) {
                e = *it;
            } else {
                res.push_back({s, e});
                s = e = *it;
            }
        }

        res.push_back({s, e});

        return res;
    }
};


/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */
