#include <stdio.h>
#include <limits.h>
struct Result {
    int start;
    int end;
    int sum;
};
struct Result FindMaxCrossingSum(int resource[], int low, int mid, int high) {
    int leftSum = INT_MIN;
    int sum = 0;
    int maxLeft = mid;
    for (int i = mid; i >= low; i--) {
        sum += resource[i];
        if (sum > leftSum) {
            leftSum = sum;
            maxLeft = i;
        }
    }
    int rightSum = INT_MIN;
    sum = 0;
    int maxRight = mid + 1;
    for (int j = mid + 1; j <= high; j++) {
        sum += resource[j];
        if (sum > rightSum) {
            rightSum = sum;
            maxRight = j;
        }
    }
    struct Result cross = {maxLeft, maxRight, leftSum + rightSum};
    return cross;
}
struct Result FindMaxSubarray(int resource[], int low, int high) {
    if (low == high) {
        struct Result base = {low, high, resource[low]};
        return base;
    }
    int mid = (low + high) / 2;
    struct Result left = FindMaxSubarray(resource, low, mid);
    struct Result right = FindMaxSubarray(resource, mid + 1, high);
    struct Result cross = FindMaxCrossingSum(resource, low, mid, high);
    if (left.sum >= right.sum && left.sum >= cross.sum)
        return left;
    else if (right.sum >= left.sum && right.sum >= cross.sum)
        return right;
    else
        return cross;
}
int main() {
    int n = 6;
    int resource[] = {5, 1, -2, 8, 3, -4};
    struct Result ans = FindMaxSubarray(resource, 0, n - 1);
    printf("start index %d\n end index %d\n sum %d\n", ans.start, ans.end, ans.sum);
    return 0;
}
