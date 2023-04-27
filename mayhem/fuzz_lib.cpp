#include "fuzzer/FuzzedDataProvider.h"
#include "csv.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider fdp(data, size);
    try {
        if (fdp.ConsumeBool()) {
            // Test the LineReader
            auto buff = fdp.ConsumeRemainingBytesAsString();
            io::LineReader reader{"fuzz.in", buff.c_str(), buff.c_str() + buff.size()};
            while (reader.next_line());
        } else {
            // Test the CSVReader
            auto buff = fdp.ConsumeRemainingBytesAsString();
            io::CSVReader<4, io::trim_chars<' '>, io::no_quote_escape<','>> in("fuzz.in", buff.c_str(), buff.c_str() + buff.size());
            int w;
            std::string x, y;
            double z;
            while (in.read_row(w, x, y, z));
        }
    } catch (const io::error::base &e) {
        return -1;
    }

    return 0;
}
