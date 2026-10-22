# Contains Duplicate — Session Notes

**Date:** 2026-10-22 · **Difficulty:** Easy · **Pattern:** Hashing (seen-set)

## Problem
Given an integer array `nums`, return `true` if any value appears at least twice, else `false`.

## My attempts
| Submission | Approach | Result |
|---|---|---|
| (pre-submit draft) | `unordered_map` with `if (mp[a] > 1)` | **Wrong** — off-by-one |
| `submission-0.cpp` | `unordered_map` with `if (mp[a] > 0)` | Accepted |
| `submission-1.cpp` | `unordered_set` + `count()` | Accepted (preferred) |

## The bug I made
```cpp
if (mp[a] > 1) return true;   // on the 2nd sighting mp[a] is still 1 → 1 > 1 is false
```
Only detected a duplicate on the **third** occurrence. `[1, 2, 1]` → returned `false`.
**Fix:** `> 0`, or better, a set.

## Final solution
```cpp
bool hasDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for (int a : nums) {
        if (seen.count(a)) return true;
        seen.insert(a);
    }
    return false;
}
```
- **Time:** O(n) · **Space:** O(n)

## Alternatives / trade-offs
| Approach | Time | Space |
|---|---|---|
| Brute force (all pairs) | O(n²) | O(1) |
| Sort + compare neighbours | O(n log n) | O(log n) in-place (mutates input) |
| Hash set | O(n) | O(n) |

## Edge cases
- `[1, 1]` → `true` — smallest true case; **always dry-run this**
- `[1]` → `false`
- `[1, 2, 1]` → `true` — caught my bug

## Professor's feedback
- Problem solving 4/5 · Correctness 2/5 · Complexity: not stated · Code quality 3/5
- Need presence only → **set**, not map.
- C++ trap: `mp[key]` on a missing key **inserts** it with 0. Use `.count()` / `.find()` for reads.
- Always state complexity without being asked.

## Takeaway
> Need "have I seen this before?" → hash set. Dry-run the smallest input that should return true.
