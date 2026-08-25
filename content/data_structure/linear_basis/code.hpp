using u32 = uint32_t;

struct LinearBasis {
    u32 b[32]{};

    void insert(u32 x) {
        for (int i = 31; i >= 0; i--)
            if (x >> i & 1) {
                if (b[i]) x ^= b[i];
                else return b[i] = x, void();
            }
    }

    bool check(u32 x) const {
        for (int i = 0; i < 32; i++)
            if (b[i] && __builtin_parity(x & b[i])) return false;
        return true;
    }

    LinearBasis orthogonal_complement() const {
        LinearBasis res;
        for (int i = 0; i < 32; i++) if (!b[i]) {
            u32 x = 1u << i;
            for (int j = 0; j < 32; j++)
                if (b[j] && __builtin_parity(b[j] & x)) x ^= 1u << j;
            res.insert(x);
        }
        return res;
    }

    LinearBasis merge(const LinearBasis& t) const {
        LinearBasis res = *this;
        for (u32 x : t.b) res.insert(x);
        return res;
    }
};
