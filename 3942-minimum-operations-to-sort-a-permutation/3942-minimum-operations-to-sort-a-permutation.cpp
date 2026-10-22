class Solution {
public:
    int minOperations(vector<int>& nums) {
     int n=nums.size();
        int p=-1;
        for(int i=0;i<n;i++){
            if(nums[i]==0){
                p=i;
                break;
            }
        }
        bool inc=true;
        for(int i=0;i<n;i++){
            if(nums[(p+i)%n]!=i){
                inc=false;
                break;
            }
        }
        bool dec=true;
        for(int i=0;i<n;i++){
            if(nums[(p-i+n)%n]!=i){
                dec=false;
                break;
            }
        }
        int ans=1e9;
        if(inc){
            ans=min({ans,p,n-p+2});
        }
        if(dec){
            int k=(p+1)%n;
            ans=min({ans,k+1,n-k+1});
        }
        return ans==1e9?-1:ans;
    }
};