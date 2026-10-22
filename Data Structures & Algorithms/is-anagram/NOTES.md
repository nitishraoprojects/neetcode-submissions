# Valid Anagram — Session Notes

**Date:** 2026-10-22 · **Difficulty:** Easy · **Pattern:** Frequency counting

## Problem
Given strings `s` and `t`, return `true` if `t` is an anagram of `s`.
**Constraints (asked the interviewer):** `1 <= s.length, t.length <= 5 × 10⁴`, lowercase English letters only.

## How the discussion went
1. **Clarifying question:** asked about input length ✅ — n = 5×10⁴ rules out O(n²); target O(n log n) or better.
2. **Brute force:** sort both and compare ✅ (forgot to state complexity at first).
3. **First "optimized" idea:** set + "reject if any letter count is odd" ❌
   - A set can't count.
   - Parity ≠ equality. Counter-example: `s = "aa"`, `t = "bb"` → all combined counts even, but not anagrams.
4. **Fixed idea:** two hash maps, compare counts ✅
   - Iterating only one map is unsafe **without** a length check: `s = "a"`, `t = "ab"` → wrongly `true`.
5. **Quick check:** first said "if either string is empty → false" ❌ (constraints say length ≥ 1, and `""`/`""` *are* anagrams). Correct check: **lengths differ → false** (needed Hint 1).
6. **Space complexity:** map is O(1) ✅ — at most 26 keys. Say it as "O(k), k = alphabet size = 26 → O(1)".

## My submissions
| Submission | Approach | Notes |
|---|---|---|
| draft | two maps | **Compile errors:** `s.length` (missing `()`), `mp[a]` where `a` is a `pair` |
| `submission-0.cpp` | two maps | Accepted. Redundant lookup `mp[a.first]` (use `a.second`); `mp1[...]` inserts keys |
| `submission-1.cpp` | one map, `++` for `s`, `--` for `t` | Accepted. Needed Hint 1 (bank account: deposit/debit). Early exit not implemented |

## Why checking only `< 0` is enough
With equal lengths, total deposits = total debits. If any balance were positive, another must be negative.
So: **length check + no balance goes negative ⇒ all balances are zero.**

## Final (tight) solution
```cpp
bool isAnagram(string s, string t) {
    if (s.length() != t.length()) return false;

    int count[26] = {0};
    for (char c : s) count[c - 'a']++;
    for (char c : t) {
        if (--count[c - 'a'] < 0) return false;   // early exit
    }
    return true;
}
```
- **Time:** O(n) · **Space:** O(1) (26 ints)
- Fixed array beats hash map when the alphabet is small and known — **use the constraints**.

## Complexity summary
| Approach | Time | Space |
|---|---|---|
| Sort + compare | O(n log n) | O(log n) in-place (mutates input) / O(n) if copying |
| Two hash maps | O(n) | O(k) → O(1) for 26 letters |
| One count array + early exit | O(n) | O(1) |

## Edge cases
- `"anagram"`, `"nagaram"` → `true`
- `"rat"`, `"car"` → `false`
- `"a"`, `"ab"` → `false` (length check)
- `"aa"`, `"bb"` → `false` (kills the parity idea)

## Follow-up: Unicode input (got 2/5)
- I said "use ASCII codes" — **wrong**: ASCII = 128 chars; Unicode ≈ 1.1M code points.
- Array indexing no longer works → back to **hash map keyed by code point**; space O(k), k ≤ n.
- C++ trap: `std::string` holds **UTF-8 bytes**; `for (char c : s)` iterates bytes, not characters. Decode to `char32_t` / `std::u32string`.
- Senior bonus: normalize first (NFC) — `é` can be one code point or `e` + combining accent.

## Professor's feedback
| Criterion | Score |
|---|---|
| Problem solving | 4/5 |
| Correctness | 4/5 |
| Complexity | 4/5 |
| Code quality | 3/5 — names `mp`/`mp1`, `auto` copies pairs (use `const auto&`) |
| Communication | 2/5 — one-word answers; **skipped hand dry-runs 3 times** |
| **Verdict** | **Lean hire** |

## Action items
- [ ] Dry-run by hand before every submit (no submit button in the real interview)
- [ ] Meaningful names: `countS`, `freq`, not `mp`, `mp1`
- [ ] Answer in full sentences
- [ ] Get a working solution first, then optimize

## Takeaway
> "Same elements, any order" → frequency count. Small fixed alphabet → `int[26]`. Length check first.
