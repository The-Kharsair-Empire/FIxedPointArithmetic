#include "iostream"

// template <size_t dp>
// constexpr int32_t DoubleToFixed(double d)
// {
//     return int32_t(d * double(1 << dp) + (d >= 0 ? 0.5 : -0.5)); // bias padding to the last digit.
//     //double (1 << dp) = 2 ^ dp
// }
 
// template <size_t dp>
// constexpr double FixedToDouble(int32_t f)
// {
//     return double(f) / double(1 << dp);
// }


template <class T1, class T2, size_t dp>
class FixedPoint
{
public:
    T1 value = T1(0);
    constexpr FixedPoint() = default;
    constexpr FixedPoint(const double d) 
    {
        value = T1(d * double(1 << dp) + (d >= 0 ? 0.5 : -0.5));
    }

    constexpr operator double() const
    {
        return double(value) / double(1 << dp);
    }

public:

    constexpr FixedPoint& operator=(const FixedPoint& f) = default;

    constexpr FixedPoint operator-() const
    {
        return form(-this->value);
    }


    constexpr FixedPoint operator+(const FixedPoint& f) const
    {
        return form(this->value + f.value);
    }

    constexpr FixedPoint& operator+=(const FixedPoint& f) 
    {
        this->value += f.value;
        return *this;
    }

    constexpr FixedPoint operator-(const FixedPoint& f) const
    {
        return form(this->value - f.value);
    }

    constexpr FixedPoint& operator-=(const FixedPoint& f) 
    {
        this->value -= f.value;
        return *this;
    }


    constexpr FixedPoint operator*(const FixedPoint& f) const
    {
        
        return form((T2(this->value) * T2(f.value)) >> dp);
    }

    constexpr FixedPoint& operator*=(const FixedPoint& f) 
    {
        this->value = (T2(this->value) * T2(f.value)) >> dp;
        return *this;
    }

    constexpr FixedPoint operator/(const FixedPoint& f) const
    {
        return form((T2(this->value) <<dp) / T2(f.value));
    }

    constexpr FixedPoint& operator/=(const FixedPoint& f) 
    {
        this->value = (T2(this->value) <<dp) / T2(f.value);
        return *this;
    }



private:
    static constexpr FixedPoint form(T1 val)
    {
        FixedPoint f;
        f.value = val;
        return f;
    }

};


FixedPoint<int32_t, int64_t, 16> constexpr operator "" _fp1616(const long double n)
{
    return FixedPoint<int32_t, int64_t, 16>(double(n));
}

FixedPoint<int16_t, int32_t, 8> constexpr operator "" _fp88(const long double n)
{
    return FixedPoint<int16_t, int32_t, 8>(double(n));
}

FixedPoint<int8_t, int16_t, 4> constexpr operator "" _fp44(const long double n)
{
    return FixedPoint<int8_t, int16_t, 4>(double(n));
}

int main() {

    constexpr double r = 4.5679_fp1616 + 17.4563_fp1616;
    constexpr double wtf = 34.5679_fp44 + 48.4563_fp44;
    // using fp16_16 = FixedPoint<int32_t, int64_t, 16>;
    // using fp8_8 = FixedPoint<int16_t, int32_t, 8>;
    // using fp4_4 = FixedPoint<int8_t, int16_t, 4>;

    // constexpr fp4_4 a(5.34);
    // constexpr fp4_4 b(7.22);

    // constexpr double c = double(a * b);

    // std::cout <<  c << std::endl;
 


    // constexpr auto a = 3.5 * double (1 << 16);

    //16.16
    // constexpr int32_t fixed1 = DoubleToFixed<16>(4.42);
    // constexpr int32_t fixed2 = DoubleToFixed<16>(6.38);
    // constexpr int32_t fixed3 = fixed1 + fixed2;
    // constexpr int32_t fixed4 = fixed1 - fixed2;
    // constexpr int32_t fixed5 = (int64_t(fixed1) * int64_t(fixed2)) >> 16;
    // constexpr int32_t fixed6 = (int64_t(fixed1) << 16) / int64_t(fixed2);
    // constexpr double ft1 = FixedToDouble<16>(fixed3);
    // constexpr double ft2 = FixedToDouble<16>(fixed4);
    // constexpr double ft3 = FixedToDouble<16>(fixed5);
    // constexpr double ft4 = FixedToDouble<16>(fixed6);


    //28.4
    // constexpr int32_t fixed1 = DoubleToFixed<4>(4.42);
    // constexpr int32_t fixed2 = DoubleToFixed<4>(6.38);
    // constexpr int32_t fixed3 = fixed1 + fixed2;
    // constexpr int32_t fixed4 = fixed1 - fixed2;
    // constexpr int32_t fixed5 = (int64_t(fixed1) * int64_t(fixed2)) >> 4;
    // constexpr int32_t fixed6 = (int64_t(fixed1) << 4) / int64_t(fixed2);
    // constexpr double ft1 = FixedToDouble<4>(fixed1);
    // constexpr double ft2 = FixedToDouble<4>(fixed4);
    // constexpr double ft3 = FixedToDouble<4>(fixed5);
    // constexpr double ft4 = FixedToDouble<4>(fixed6);
    return 0;
} 