#ifndef CONVERSION
#define CONVERSION
        template <typename T>
        std::string showLD(T value)
        {
            std::ostringstream oss;
            oss << std::scientific << std::setprecision(16) << value;
            return oss.str();
        }

std::string showLD2(long double val) {
    constexpr int BUFS = 64;
    char buf[BUFS];

    snprintf(buf, BUFS, "%.32LE", val);
    return std::string(buf);
}
#endif // CONVERSION

