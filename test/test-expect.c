/*
 * Copyright (c) 2015 Nicholas Fraser
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test-expect.h"

#if MPACK_EXPECT

// tests the example on the messagepack homepage
static void test_expect_example_read() {
    static const char test[] = "\x82\xA7""compact\xC3\xA6""schema\x00";
    mpack_reader_t reader;
    mpack_reader_init_data(&reader, test, sizeof(test) - 1);

    test_assert(2 == mpack_expect_map(&reader));
    mpack_expect_cstr_match(&reader, "compact");
    test_assert(true == mpack_expect_bool(&reader));
    mpack_expect_cstr_match(&reader, "schema");
    test_assert(0 == mpack_expect_u8(&reader));
    mpack_done_map(&reader);

    test_reader_destroy_noerror(&reader);
}

/*
   [
   1,-32,128,-129,65536,-65537,2147483649,-2147483648,9223372036854775807,-9223372036854775808,
   ]
   */

static void test_expect_uint_fixnum() {

    // positive fixnums with u8
    test_simple_read("\x00", 0 == mpack_expect_u8(&reader));
    test_simple_read("\x01", 1 == mpack_expect_u8(&reader));
    test_simple_read("\x02", 2 == mpack_expect_u8(&reader));
    test_simple_read("\x0f", 0x0f == mpack_expect_u8(&reader));
    test_simple_read("\x10", 0x10 == mpack_expect_u8(&reader));
    test_simple_read("\x7f", 0x7f == mpack_expect_u8(&reader));

    // positive fixnums with u16
    test_simple_read("\x00", 0 == mpack_expect_u16(&reader));
    test_simple_read("\x01", 1 == mpack_expect_u16(&reader));
    test_simple_read("\x02", 2 == mpack_expect_u16(&reader));
    test_simple_read("\x0f", 0x0f == mpack_expect_u16(&reader));
    test_simple_read("\x10", 0x10 == mpack_expect_u16(&reader));
    test_simple_read("\x7f", 0x7f == mpack_expect_u16(&reader));

    // positive fixnums with u32
    test_simple_read("\x00", 0 == mpack_expect_u32(&reader));
    test_simple_read("\x01", 1 == mpack_expect_u32(&reader));
    test_simple_read("\x02", 2 == mpack_expect_u32(&reader));
    test_simple_read("\x0f", 0x0f == mpack_expect_u32(&reader));
    test_simple_read("\x10", 0x10 == mpack_expect_u32(&reader));
    test_simple_read("\x7f", 0x7f == mpack_expect_u32(&reader));

    // positive fixnums with u64
    test_simple_read("\x00", 0 == mpack_expect_u64(&reader));
    test_simple_read("\x01", 1 == mpack_expect_u64(&reader));
    test_simple_read("\x02", 2 == mpack_expect_u64(&reader));
    test_simple_read("\x0f", 0x0f == mpack_expect_u64(&reader));
    test_simple_read("\x10", 0x10 == mpack_expect_u64(&reader));
    test_simple_read("\x7f", 0x7f == mpack_expect_u64(&reader));

}

static void test_expect_uint_signed_fixnum() {

    // positive fixnums with i8
    test_simple_read("\x00", 0 == mpack_expect_i8(&reader));
    test_simple_read("\x01", 1 == mpack_expect_i8(&reader));
    test_simple_read("\x02", 2 == mpack_expect_i8(&reader));
    test_simple_read("\x0f", 0x0f == mpack_expect_i8(&reader));
    test_simple_read("\x10", 0x10 == mpack_expect_i8(&reader));
    test_simple_read("\x7f", 0x7f == mpack_expect_i8(&reader));

    // positive fixnums with i16
    test_simple_read("\x00", 0 == mpack_expect_i16(&reader));
    test_simple_read("\x01", 1 == mpack_expect_i16(&reader));
    test_simple_read("\x02", 2 == mpack_expect_i16(&reader));
    test_simple_read("\x0f", 0x0f == mpack_expect_i16(&reader));
    test_simple_read("\x10", 0x10 == mpack_expect_i16(&reader));
    test_simple_read("\x7f", 0x7f == mpack_expect_i16(&reader));

    // positive fixnums with i32
    test_simple_read("\x00", 0 == mpack_expect_i32(&reader));
    test_simple_read("\x01", 1 == mpack_expect_i32(&reader));
    test_simple_read("\x02", 2 == mpack_expect_i32(&reader));
    test_simple_read("\x0f", 0x0f == mpack_expect_i32(&reader));
    test_simple_read("\x10", 0x10 == mpack_expect_i32(&reader));
    test_simple_read("\x7f", 0x7f == mpack_expect_i32(&reader));

    // positive fixnums with i64
    test_simple_read("\x00", 0 == mpack_expect_i64(&reader));
    test_simple_read("\x01", 1 == mpack_expect_i64(&reader));
    test_simple_read("\x02", 2 == mpack_expect_i64(&reader));
    test_simple_read("\x0f", 0x0f == mpack_expect_i64(&reader));
    test_simple_read("\x10", 0x10 == mpack_expect_i64(&reader));
    test_simple_read("\x7f", 0x7f == mpack_expect_i64(&reader));

}

static void test_expect_negative_fixnum() {

    // negative fixnums with i8
    test_simple_read("\xff", -1 == mpack_expect_i8(&reader));
    test_simple_read("\xfe", -2 == mpack_expect_i8(&reader));
    test_simple_read("\xf0", -16 == mpack_expect_i8(&reader));
    test_simple_read("\xe0", -32 == mpack_expect_i8(&reader));

    // negative fixnums with i16
    test_simple_read("\xff", -1 == mpack_expect_i16(&reader));
    test_simple_read("\xfe", -2 == mpack_expect_i16(&reader));
    test_simple_read("\xf0", -16 == mpack_expect_i16(&reader));
    test_simple_read("\xe0", -32 == mpack_expect_i16(&reader));

    // negative fixnums with i32
    test_simple_read("\xff", -1 == mpack_expect_i32(&reader));
    test_simple_read("\xfe", -2 == mpack_expect_i32(&reader));
    test_simple_read("\xf0", -16 == mpack_expect_i32(&reader));
    test_simple_read("\xe0", -32 == mpack_expect_i32(&reader));

    // negative fixnums with i64
    test_simple_read("\xff", -1 == mpack_expect_i64(&reader));
    test_simple_read("\xfe", -2 == mpack_expect_i64(&reader));
    test_simple_read("\xf0", -16 == mpack_expect_i64(&reader));
    test_simple_read("\xe0", -32 == mpack_expect_i64(&reader));

}

static void test_expect_uint() {

    // positive signed into u8
    test_simple_read("\xd0\x7f", 0x7f == mpack_expect_u8(&reader));
    test_simple_read("\xd0\x7f", 0x7f == mpack_expect_u16(&reader));
    test_simple_read("\xd0\x7f", 0x7f == mpack_expect_u32(&reader));
    test_simple_read("\xd0\x7f", 0x7f == mpack_expect_u64(&reader));
    test_simple_read("\xd0\x7f", 0x7f == mpack_expect_uint(&reader));
    test_simple_read("\xd1\x7f\xff", 0x7fff == mpack_expect_u16(&reader));
    test_simple_read("\xd1\x7f\xff", 0x7fff == mpack_expect_u32(&reader));
    test_simple_read("\xd1\x7f\xff", 0x7fff == mpack_expect_u64(&reader));
    test_simple_read("\xd1\x7f\xff", 0x7fff == mpack_expect_uint(&reader));
    test_simple_read("\xd2\x7f\xff\xff\xff", 0x7fffffff == mpack_expect_u32(&reader));
    test_simple_read("\xd2\x7f\xff\xff\xff", 0x7fffffff == mpack_expect_u64(&reader));
    test_simple_read("\xd2\x7f\xff\xff\xff", 0x7fffffff == mpack_expect_uint(&reader));
    test_simple_read("\xd3\x7f\xff\xff\xff\xff\xff\xff\xff", 0x7fffffffffffffff == mpack_expect_u64(&reader));

    // positive unsigned into u8
    
    test_simple_read("\xcc\x80", 0x80 == mpack_expect_u8(&reader));
    test_simple_read("\xcc\x80", 0x80 == mpack_expect_u16(&reader));
    test_simple_read("\xcc\x80", 0x80 == mpack_expect_u32(&reader));
    test_simple_read("\xcc\x80", 0x80 == mpack_expect_u64(&reader));
    test_simple_read("\xcc\x80", 0x80 == mpack_expect_uint(&reader));

    test_simple_read("\xcc\xff", 0xff == mpack_expect_u8(&reader));
    test_simple_read("\xcc\xff", 0xff == mpack_expect_u16(&reader));
    test_simple_read("\xcc\xff", 0xff == mpack_expect_u32(&reader));
    test_simple_read("\xcc\xff", 0xff == mpack_expect_u64(&reader));
    test_simple_read("\xcc\xff", 0xff == mpack_expect_uint(&reader));

    test_simple_read("\xcd\x01\x00", 0x100 == mpack_expect_u16(&reader));
    test_simple_read("\xcd\x01\x00", 0x100 == mpack_expect_u32(&reader));
    test_simple_read("\xcd\x01\x00", 0x100 == mpack_expect_u64(&reader));
    test_simple_read("\xcd\x01\x00", 0x100 == mpack_expect_uint(&reader));

    test_simple_read("\xcd\xff\xff", 0xffff == mpack_expect_u16(&reader));
    test_simple_read("\xcd\xff\xff", 0xffff == mpack_expect_u32(&reader));
    test_simple_read("\xcd\xff\xff", 0xffff == mpack_expect_u64(&reader));
    test_simple_read("\xcd\xff\xff", 0xffff == mpack_expect_uint(&reader));

    test_simple_read("\xce\x00\x01\x00\x00", 0x10000 == mpack_expect_u32(&reader));
    test_simple_read("\xce\x00\x01\x00\x00", 0x10000 == mpack_expect_u64(&reader));
    test_simple_read("\xce\x00\x01\x00\x00", 0x10000 == mpack_expect_uint(&reader));

    test_simple_read("\xce\xff\xff\xff\xff", 0xffffffff == mpack_expect_u32(&reader));
    test_simple_read("\xce\xff\xff\xff\xff", 0xffffffff == mpack_expect_u64(&reader));
    test_simple_read("\xce\xff\xff\xff\xff", 0xffffffff == mpack_expect_uint(&reader));

    test_simple_read("\xcf\x00\x00\x00\x01\x00\x00\x00\x00", 0x100000000 == mpack_expect_u64(&reader));
    test_simple_read("\xcf\xff\xff\xff\xff\xff\xff\xff\xff", 0xffffffffffffffff == mpack_expect_u64(&reader));

}

static void test_expect_uint_signed() {

    test_simple_read("\xcc\x80", 0x80 == mpack_expect_i16(&reader));
    test_simple_read("\xcc\x80", 0x80 == mpack_expect_i32(&reader));
    test_simple_read("\xcc\x80", 0x80 == mpack_expect_i64(&reader));
    test_simple_read("\xcc\x80", 0x80 == mpack_expect_int(&reader));

    test_simple_read("\xcc\xff", 0xff == mpack_expect_i16(&reader));
    test_simple_read("\xcc\xff", 0xff == mpack_expect_i32(&reader));
    test_simple_read("\xcc\xff", 0xff == mpack_expect_i64(&reader));
    test_simple_read("\xcc\xff", 0xff == mpack_expect_int(&reader));

    test_simple_read("\xcd\x01\x00", 0x100 == mpack_expect_i16(&reader));
    test_simple_read("\xcd\x01\x00", 0x100 == mpack_expect_i32(&reader));
    test_simple_read("\xcd\x01\x00", 0x100 == mpack_expect_i64(&reader));
    test_simple_read("\xcd\x01\x00", 0x100 == mpack_expect_int(&reader));

    test_simple_read("\xcd\xff\xff", 0xffff == mpack_expect_i32(&reader));
    test_simple_read("\xcd\xff\xff", 0xffff == mpack_expect_i64(&reader));
    test_simple_read("\xcd\xff\xff", 0xffff == mpack_expect_int(&reader));

    test_simple_read("\xce\x00\x01\x00\x00", 0x10000 == mpack_expect_i32(&reader));
    test_simple_read("\xce\x00\x01\x00\x00", 0x10000 == mpack_expect_i64(&reader));
    test_simple_read("\xce\x00\x01\x00\x00", 0x10000 == mpack_expect_int(&reader));

    test_simple_read("\xce\xff\xff\xff\xff", 0xffffffff == mpack_expect_i64(&reader));

    test_simple_read("\xcf\x00\x00\x00\x01\x00\x00\x00\x00", 0x100000000 == mpack_expect_i64(&reader));

}

static void test_expect_int() {

    test_simple_read("\xd0\xdf", -33 == mpack_expect_i8(&reader));
    test_simple_read("\xd0\xdf", -33 == mpack_expect_i16(&reader));
    test_simple_read("\xd0\xdf", -33 == mpack_expect_i32(&reader));
    test_simple_read("\xd0\xdf", -33 == mpack_expect_i64(&reader));
    test_simple_read("\xd0\xdf", -33 == mpack_expect_int(&reader));

    test_simple_read("\xd0\x80", INT8_MIN == mpack_expect_i8(&reader));
    test_simple_read("\xd0\x80", INT8_MIN == mpack_expect_i16(&reader));
    test_simple_read("\xd0\x80", INT8_MIN == mpack_expect_i32(&reader));
    test_simple_read("\xd0\x80", INT8_MIN == mpack_expect_i64(&reader));
    test_simple_read("\xd0\x80", INT8_MIN == mpack_expect_int(&reader));

    test_simple_read("\xd1\xff\x7f", INT8_MIN - 1 == mpack_expect_i16(&reader));
    test_simple_read("\xd1\xff\x7f", INT8_MIN - 1 == mpack_expect_i32(&reader));
    test_simple_read("\xd1\xff\x7f", INT8_MIN - 1 == mpack_expect_i64(&reader));
    test_simple_read("\xd1\xff\x7f", INT8_MIN - 1 == mpack_expect_int(&reader));

    test_simple_read("\xd1\x80\x00", INT16_MIN == mpack_expect_i16(&reader));
    test_simple_read("\xd1\x80\x00", INT16_MIN == mpack_expect_i32(&reader));
    test_simple_read("\xd1\x80\x00", INT16_MIN == mpack_expect_i64(&reader));
    test_simple_read("\xd1\x80\x00", INT16_MIN == mpack_expect_int(&reader));

    test_simple_read("\xd2\xff\xff\x7f\xff", INT16_MIN - 1 == mpack_expect_i32(&reader));
    test_simple_read("\xd2\xff\xff\x7f\xff", INT16_MIN - 1 == mpack_expect_i64(&reader));
    test_simple_read("\xd2\xff\xff\x7f\xff", INT16_MIN - 1 == mpack_expect_int(&reader));

    test_simple_read("\xd2\x80\x00\x00\x00", INT32_MIN == mpack_expect_i32(&reader));
    test_simple_read("\xd2\x80\x00\x00\x00", INT32_MIN == mpack_expect_i64(&reader));
    test_simple_read("\xd2\x80\x00\x00\x00", INT32_MIN == mpack_expect_int(&reader));

    test_simple_read("\xd3\xff\xff\xff\xff\x7f\xff\xff\xff", (int64_t)INT32_MIN - 1 == mpack_expect_i64(&reader));

    test_simple_read("\xd3\x80\x00\x00\x00\x00\x00\x00\x00", INT64_MIN == mpack_expect_i64(&reader));

}

static void test_expect_ints_dynamic_int() {

    // we don't bother to test with different signed/unsigned value
    // functions; they are tested for equality in test-value.c

    // positive fixnums
    test_simple_read("\x00", mpack_tag_equal(mpack_tag_uint(0), mpack_read_tag(&reader)));
    test_simple_read("\x01", mpack_tag_equal(mpack_tag_uint(1), mpack_read_tag(&reader)));
    test_simple_read("\x02", mpack_tag_equal(mpack_tag_uint(2), mpack_read_tag(&reader)));
    test_simple_read("\x0f", mpack_tag_equal(mpack_tag_uint(0x0f), mpack_read_tag(&reader)));
    test_simple_read("\x10", mpack_tag_equal(mpack_tag_uint(0x10), mpack_read_tag(&reader)));
    test_simple_read("\x7f", mpack_tag_equal(mpack_tag_uint(0x7f), mpack_read_tag(&reader)));

    // negative fixnums
    test_simple_read("\xff", mpack_tag_equal(mpack_tag_int(-1), mpack_read_tag(&reader)));
    test_simple_read("\xfe", mpack_tag_equal(mpack_tag_int(-2), mpack_read_tag(&reader)));
    test_simple_read("\xf0", mpack_tag_equal(mpack_tag_int(-16), mpack_read_tag(&reader)));
    test_simple_read("\xe0", mpack_tag_equal(mpack_tag_int(-32), mpack_read_tag(&reader)));

    // uints
    test_simple_read("\xcc\x80", mpack_tag_equal(mpack_tag_uint(0x80), mpack_read_tag(&reader)));
    test_simple_read("\xcc\xff", mpack_tag_equal(mpack_tag_uint(0xff), mpack_read_tag(&reader)));
    test_simple_read("\xcd\x01\x00", mpack_tag_equal(mpack_tag_uint(0x100), mpack_read_tag(&reader)));
    test_simple_read("\xcd\xff\xff", mpack_tag_equal(mpack_tag_uint(0xffff), mpack_read_tag(&reader)));
    test_simple_read("\xce\x00\x01\x00\x00", mpack_tag_equal(mpack_tag_uint(0x10000), mpack_read_tag(&reader)));
    test_simple_read("\xce\xff\xff\xff\xff", mpack_tag_equal(mpack_tag_uint(0xffffffff), mpack_read_tag(&reader)));
    test_simple_read("\xcf\x00\x00\x00\x01\x00\x00\x00\x00", mpack_tag_equal(mpack_tag_uint(UINT64_C(0x100000000)), mpack_read_tag(&reader)));
    test_simple_read("\xcf\xff\xff\xff\xff\xff\xff\xff\xff", mpack_tag_equal(mpack_tag_uint(UINT64_C(0xffffffffffffffff)), mpack_read_tag(&reader)));

    // ints
    test_simple_read("\xd0\xdf", mpack_tag_equal(mpack_tag_int(-33), mpack_read_tag(&reader)));
    test_simple_read("\xd0\x80", mpack_tag_equal(mpack_tag_int(INT8_MIN), mpack_read_tag(&reader)));
    test_simple_read("\xd1\xff\x7f", mpack_tag_equal(mpack_tag_int(INT8_MIN - 1), mpack_read_tag(&reader)));
    test_simple_read("\xd1\x80\x00", mpack_tag_equal(mpack_tag_int(INT16_MIN), mpack_read_tag(&reader)));
    test_simple_read("\xd2\xff\xff\x7f\xff", mpack_tag_equal(mpack_tag_int(INT16_MIN - 1), mpack_read_tag(&reader)));

    test_simple_read("\xd2\x80\x00\x00\x00", mpack_tag_equal(mpack_tag_int(INT32_MIN), mpack_read_tag(&reader)));
    test_simple_read("\xd3\xff\xff\xff\xff\x7f\xff\xff\xff", mpack_tag_equal(mpack_tag_int((int64_t)INT32_MIN - 1), mpack_read_tag(&reader)));

    test_simple_read("\xd3\x80\x00\x00\x00\x00\x00\x00\x00", mpack_tag_equal(mpack_tag_int(INT64_MIN), mpack_read_tag(&reader)));

}

static void test_expect_int_bounds() {

    test_simple_read_error("\xd1\xff\x7f", 0 == mpack_expect_i8(&reader), mpack_error_type); 
    test_simple_read_error("\xd1\x80\x00", 0 == mpack_expect_i8(&reader), mpack_error_type);

    test_simple_read_error("\xd2\xff\xff\x7f\xff", 0 == mpack_expect_i8(&reader), mpack_error_type);
    test_simple_read_error("\xd2\xff\xff\x7f\xff", 0 == mpack_expect_i16(&reader), mpack_error_type);

    test_simple_read_error("\xd2\x80\x00\x00\x00", 0 == mpack_expect_i8(&reader), mpack_error_type);
    test_simple_read_error("\xd2\x80\x00\x00\x00", 0 == mpack_expect_i16(&reader), mpack_error_type);

    test_simple_read_error("\xd3\xff\xff\xff\xff\x7f\xff\xff\xff", 0 == mpack_expect_i8(&reader), mpack_error_type);
    test_simple_read_error("\xd3\xff\xff\xff\xff\x7f\xff\xff\xff", 0 == mpack_expect_i16(&reader), mpack_error_type);
    test_simple_read_error("\xd3\xff\xff\xff\xff\x7f\xff\xff\xff", 0 == mpack_expect_i32(&reader), mpack_error_type);

    test_simple_read_error("\xd3\x80\x00\x00\x00\x00\x00\x00\x00", 0 == mpack_expect_i8(&reader), mpack_error_type);
    test_simple_read_error("\xd3\x80\x00\x00\x00\x00\x00\x00\x00", 0 == mpack_expect_i16(&reader), mpack_error_type);
    test_simple_read_error("\xd3\x80\x00\x00\x00\x00\x00\x00\x00", 0 == mpack_expect_i32(&reader), mpack_error_type);

}

static void test_expect_uint_bounds() {

    test_simple_read_error("\xcd\x01\x00", 0 == mpack_expect_u8(&reader), mpack_error_type);
    test_simple_read_error("\xcd\xff\xff", 0 == mpack_expect_u8(&reader), mpack_error_type);

    test_simple_read_error("\xce\x00\x01\x00\x00", 0 == mpack_expect_u8(&reader), mpack_error_type);
    test_simple_read_error("\xce\x00\x01\x00\x00", 0 == mpack_expect_u16(&reader), mpack_error_type);

    test_simple_read_error("\xce\xff\xff\xff\xff", 0 == mpack_expect_u8(&reader), mpack_error_type);
    test_simple_read_error("\xce\xff\xff\xff\xff", 0 == mpack_expect_u16(&reader), mpack_error_type);

    test_simple_read_error("\xcf\x00\x00\x00\x01\x00\x00\x00\x00", 0 == mpack_expect_u8(&reader), mpack_error_type);
    test_simple_read_error("\xcf\x00\x00\x00\x01\x00\x00\x00\x00", 0 == mpack_expect_u16(&reader), mpack_error_type);
    test_simple_read_error("\xcf\x00\x00\x00\x01\x00\x00\x00\x00", 0 == mpack_expect_u32(&reader), mpack_error_type);

}

#define TEST_EXPECT_UINT_RANGE(name) \
    test_simple_read("\x00", 0 == mpack_expect_##name##_max(&reader, 0));                                  \
    test_simple_read_error("\x01", 0 == mpack_expect_##name##_max(&reader, 0), mpack_error_type);          \
                                                                                                           \
    test_simple_read_error("\x00", 1 == mpack_expect_##name##_range(&reader, 1, 3), mpack_error_type);     \
    test_simple_read("\x01", 1 == mpack_expect_##name##_range(&reader, 1, 3));                             \
    test_simple_read("\x02", 2 == mpack_expect_##name##_range(&reader, 1, 3));                             \
    test_simple_read("\x03", 3 == mpack_expect_##name##_range(&reader, 1, 3));                             \
    test_simple_read_error("\x04", 1 == mpack_expect_##name##_range(&reader, 1, 3), mpack_error_type);     \
                                                                                                           \
    test_simple_read_assert("\x00", mpack_expect_##name##_range(reader, 1, 0));

#define TEST_EXPECT_INT_RANGE(name) \
    test_simple_read("\x00", 0 == mpack_expect_##name##_max(&reader, 0));                                  \
    test_simple_read_error("\x01", 0 == mpack_expect_##name##_max(&reader, 0), mpack_error_type);          \
    test_simple_read_error("\xff", 0 == mpack_expect_##name##_max(&reader, 0), mpack_error_type);          \
                                                                                                           \
    test_simple_read_error("\xfe", -1 == mpack_expect_##name##_range(&reader, -1, 1), mpack_error_type);   \
    test_simple_read("\xff", -1 == mpack_expect_##name##_range(&reader, -1, 1));                           \
    test_simple_read("\x00", 0 == mpack_expect_##name##_range(&reader, -1, 1));                            \
    test_simple_read("\x01", 1 == mpack_expect_##name##_range(&reader, -1, 1));                            \
    test_simple_read_error("\x02", -1 == mpack_expect_##name##_range(&reader, -1, 1), mpack_error_type);   \
                                                                                                           \
    test_simple_read_assert("\x00", mpack_expect_##name##_range(reader, 1, -1));

static void test_expect_int_range() {
    // these currently don't test anything involving the limits of
    // each data type; there doesn't seem to be much point in doing
    // so, since they all wrap the normal expect functions.
    TEST_EXPECT_UINT_RANGE(u8);
    TEST_EXPECT_UINT_RANGE(u16);
    TEST_EXPECT_UINT_RANGE(u32);
    TEST_EXPECT_UINT_RANGE(u64);
    TEST_EXPECT_UINT_RANGE(uint);
    TEST_EXPECT_INT_RANGE(i8);
    TEST_EXPECT_INT_RANGE(i16);
    TEST_EXPECT_INT_RANGE(i32);
    TEST_EXPECT_INT_RANGE(i64);
    TEST_EXPECT_INT_RANGE(int);
}

static void test_expect_int_match() {
    test_simple_read("\x00", (mpack_expect_uint_match(&reader, 0), true));
    test_simple_read("\x01", (mpack_expect_uint_match(&reader, 1), true));
    test_simple_read("\xcc\x80", (mpack_expect_uint_match(&reader, 0x80), true));
    test_simple_read("\xcc\xff", (mpack_expect_uint_match(&reader, 0xff), true));
    test_simple_read("\xcd\x01\x00", (mpack_expect_uint_match(&reader, 0x100), true));
    test_simple_read("\xcd\xff\xff", (mpack_expect_uint_match(&reader, 0xffff), true));
    test_simple_read("\xce\x00\x01\x00\x00", (mpack_expect_uint_match(&reader, 0x10000), true));
    test_simple_read("\xce\xff\xff\xff\xff", (mpack_expect_uint_match(&reader, 0xffffffff), true));
    test_simple_read("\xce\xff\xff\xff\xff", (mpack_expect_uint_match(&reader, 0xffffffff), true));
    test_simple_read("\xcf\x00\x00\x00\x01\x00\x00\x00\x00", (mpack_expect_uint_match(&reader, 0x100000000), true));
    test_simple_read("\xcf\xff\xff\xff\xff\xff\xff\xff\xff", (mpack_expect_uint_match(&reader, 0xffffffffffffffff), true));

    test_simple_read("\x00", (mpack_expect_int_match(&reader, 0), true));
    test_simple_read("\x01", (mpack_expect_int_match(&reader, 1), true));
    test_simple_read("\xd0\xdf", (mpack_expect_int_match(&reader, -33), true));
    test_simple_read("\xd0\x80", (mpack_expect_int_match(&reader, INT8_MIN), true));
    test_simple_read("\xd1\xff\x7f", (mpack_expect_int_match(&reader, INT8_MIN - 1), true));
    test_simple_read("\xd1\x80\x00", (mpack_expect_int_match(&reader, INT16_MIN), true));
    test_simple_read("\xd2\xff\xff\x7f\xff", (mpack_expect_int_match(&reader, INT16_MIN - 1), true));
    test_simple_read("\xd2\x80\x00\x00\x00", (mpack_expect_int_match(&reader, INT32_MIN), true));
    test_simple_read("\xd3\xff\xff\xff\xff\x7f\xff\xff\xff", (mpack_expect_int_match(&reader, (int64_t)INT32_MIN - 1), true));
    test_simple_read("\xd3\x80\x00\x00\x00\x00\x00\x00\x00", (mpack_expect_int_match(&reader, INT64_MIN), true));

}

static void test_expect_misc() {
    test_simple_read("\xc0", (mpack_expect_nil(&reader), true));

    test_simple_read("\xc2", false == mpack_expect_bool(&reader));
    test_simple_read("\xc3", true == mpack_expect_bool(&reader));
    test_simple_read("\xc2", (mpack_expect_false(&reader), true));
    test_simple_read("\xc3", (mpack_expect_true(&reader), true));
}

#if MPACK_READ_TRACKING
static void test_expect_tracking() {
    char buf[4];
    mpack_reader_t reader;

    // tracking depth growth
    test_reader_init_str(&reader, "\x91\x91\x91\x91\x91\x91\x90");
    test_assert(1 == mpack_expect_array(&reader));
    test_assert(1 == mpack_expect_array(&reader));
    test_assert(1 == mpack_expect_array(&reader));
    test_assert(1 == mpack_expect_array(&reader));
    test_assert(1 == mpack_expect_array(&reader));
    test_assert(1 == mpack_expect_array(&reader));
    test_assert(0 == mpack_expect_array(&reader));
    mpack_done_array(&reader);
    mpack_done_array(&reader);
    mpack_done_array(&reader);
    mpack_done_array(&reader);
    mpack_done_array(&reader);
    mpack_done_array(&reader);
    mpack_done_array(&reader);
    test_reader_destroy_noerror(&reader);

    // cancel
    test_reader_init_str(&reader, "\x90");
    mpack_expect_array(&reader);
    mpack_reader_destroy_cancel(&reader);

    // done type when nothing was open
    test_reader_init_str(&reader, "\x90");
    test_expecting_break((mpack_done_map(&reader), true));
    test_reader_destroy_error(&reader, mpack_error_bug);

    // closing incomplete type
    test_reader_init_str(&reader, "\x91\xc0");
    mpack_expect_array(&reader);
    test_expecting_break((mpack_done_array(&reader), true));
    test_reader_destroy_error(&reader, mpack_error_bug);

    // reading elements in a string
    test_reader_init_str(&reader, "\xa2""xx");
    mpack_expect_str(&reader);
    test_expecting_break((mpack_read_tag(&reader), true));
    test_reader_destroy_error(&reader, mpack_error_bug);

    // reading too many elements
    test_reader_init_str(&reader, "\x90");
    mpack_expect_array(&reader);
    test_expecting_break((mpack_read_tag(&reader), true));
    test_reader_destroy_error(&reader, mpack_error_bug);

    // reading bytes with nothing open
    test_reader_init_str(&reader, "\x90");
    test_expecting_break((mpack_read_bytes(&reader, buf, sizeof(buf)), true));
    test_reader_destroy_error(&reader, mpack_error_bug);

    // reading bytes in an array
    test_reader_init_str(&reader, "\x90");
    mpack_expect_array(&reader);
    test_expecting_break((mpack_read_bytes(&reader, buf, sizeof(buf)), true));
    test_reader_destroy_error(&reader, mpack_error_bug);

    // reading too many bytes
    test_reader_init_str(&reader, "\xa2""xx");
    mpack_expect_str(&reader);
    test_expecting_break((mpack_read_bytes(&reader, buf, sizeof(buf)), true));
    test_reader_destroy_error(&reader, mpack_error_bug);

    // checking remaining bytes with unclosed type
    test_reader_init_str(&reader, "\xa2""xx");
    mpack_expect_str(&reader);
    test_expecting_break((mpack_reader_remaining(&reader, NULL), true));
    test_reader_destroy_error(&reader, mpack_error_bug);
}
#endif

static void test_expect_reals() {
    // these are some very simple floats that don't really test IEEE 742 conformance;
    // this section could use some improvement

    test_simple_read("\x00", 0.0f == mpack_expect_float(&reader));
    test_simple_read("\xd0\x00", 0.0f == mpack_expect_float(&reader));
    test_simple_read("\xca\x00\x00\x00\x00", 0.0f == mpack_expect_float(&reader));
    test_simple_read("\xcb\x00\x00\x00\x00\x00\x00\x00\x00", 0.0f == mpack_expect_float(&reader));

    test_simple_read("\x00", 0.0 == mpack_expect_double(&reader));
    test_simple_read("\xd0\x00", 0.0 == mpack_expect_double(&reader));
    test_simple_read("\xca\x00\x00\x00\x00", 0.0 == mpack_expect_double(&reader));
    test_simple_read("\xcb\x00\x00\x00\x00\x00\x00\x00\x00", 0.0 == mpack_expect_double(&reader));

    test_simple_read("\xca\xff\xff\xff\xff", isnanf(mpack_expect_float(&reader)));
    test_simple_read("\xcb\xff\xff\xff\xff\xff\xff\xff\xff", isnanf(mpack_expect_float(&reader)));
    test_simple_read("\xca\xff\xff\xff\xff", isnan(mpack_expect_double(&reader)));
    test_simple_read("\xcb\xff\xff\xff\xff\xff\xff\xff\xff", isnan(mpack_expect_double(&reader)));

    test_simple_read("\xca\x00\x00\x00\x00", 0.0f == mpack_expect_float_strict(&reader));
    test_simple_read("\xca\x00\x00\x00\x00", 0.0 == mpack_expect_double_strict(&reader));
    test_simple_read("\xcb\x00\x00\x00\x00\x00\x00\x00\x00", 0.0 == mpack_expect_double_strict(&reader));
    test_simple_read("\xca\xff\xff\xff\xff", isnanf(mpack_expect_float_strict(&reader)));
    test_simple_read("\xca\xff\xff\xff\xff", isnan(mpack_expect_double_strict(&reader)));
    test_simple_read("\xcb\xff\xff\xff\xff\xff\xff\xff\xff", isnan(mpack_expect_double_strict(&reader)));

    test_simple_read_error("\x00", 0.0f == mpack_expect_float_strict(&reader), mpack_error_type);
    test_simple_read_error("\xd0\x00", 0.0f == mpack_expect_float_strict(&reader), mpack_error_type);
    test_simple_read_error("\xcb\x00\x00\x00\x00\x00\x00\x00\x00", 0.0f == mpack_expect_float_strict(&reader), mpack_error_type);

    test_simple_read_error("\x00", 0.0 == mpack_expect_double_strict(&reader), mpack_error_type);
    test_simple_read_error("\xd0\x00", 0.0 == mpack_expect_double_strict(&reader), mpack_error_type);
}

static void test_expect_reals_range() {
    test_simple_read("\x00", 0.0f == mpack_expect_float_range(&reader, 0.0f, 0.0f));
    test_simple_read("\x00", 0.0f == mpack_expect_float_range(&reader, 0.0f, 1.0f));
    test_simple_read("\x00", 0.0f == mpack_expect_float_range(&reader, -1.0f, 0.0f));
    test_simple_read_error("\x00", 1.0f == mpack_expect_float_range(&reader, 1.0f, 2.0f), mpack_error_type);
    test_simple_read_assert("\x00", mpack_expect_float_range(reader, 1.0f, -1.0f));

    test_simple_read("\x00", 0.0 == mpack_expect_double_range(&reader, 0.0, 0.0f));
    test_simple_read("\x00", 0.0 == mpack_expect_double_range(&reader, 0.0, 1.0f));
    test_simple_read("\x00", 0.0 == mpack_expect_double_range(&reader, -1.0, 0.0f));
    test_simple_read_error("\x00", 1.0 == mpack_expect_double_range(&reader, 1.0, 2.0f), mpack_error_type);
    test_simple_read_assert("\x00", mpack_expect_double_range(reader, 1.0, -1.0));
}

static void test_expect_bad_type() {
    // test that all reader functions correctly handle badly typed data
    test_simple_read_error("\xc2", (mpack_expect_nil(&reader), true), mpack_error_type);
    test_simple_read_error("\xc0", false == mpack_expect_bool(&reader), mpack_error_type);
    test_simple_read_error("\xc0", 0 == mpack_expect_u8(&reader), mpack_error_type);
    test_simple_read_error("\xc0", 0 == mpack_expect_u16(&reader), mpack_error_type);
    test_simple_read_error("\xc0", 0 == mpack_expect_u32(&reader), mpack_error_type);
    test_simple_read_error("\xc0", 0 == mpack_expect_u64(&reader), mpack_error_type);
    test_simple_read_error("\xc0", 0 == mpack_expect_i8(&reader), mpack_error_type);
    test_simple_read_error("\xc0", 0 == mpack_expect_i16(&reader), mpack_error_type);
    test_simple_read_error("\xc0", 0 == mpack_expect_i32(&reader), mpack_error_type);
    test_simple_read_error("\xc0", 0 == mpack_expect_i64(&reader), mpack_error_type);
    test_simple_read_error("\xc0", 0.0f == mpack_expect_float(&reader), mpack_error_type);
    test_simple_read_error("\xc0", 0.0 == mpack_expect_double(&reader), mpack_error_type);
    test_simple_read_error("\xc0", 0.0f == mpack_expect_float_strict(&reader), mpack_error_type);
    test_simple_read_error("\xc0", 0.0 == mpack_expect_double_strict(&reader), mpack_error_type);
}

static void test_expect_pre_error() {
    // test that all reader functinvalidns correctly handle pre-existing errors
    test_simple_read_error("", (mpack_expect_nil(&reader), true), mpack_error_invalid);
    test_simple_read_error("", false == mpack_expect_bool(&reader), mpack_error_invalid);
    test_simple_read_error("", 0 == mpack_expect_u8(&reader), mpack_error_invalid);
    test_simple_read_error("", 0 == mpack_expect_u16(&reader), mpack_error_invalid);
    test_simple_read_error("", 0 == mpack_expect_u32(&reader), mpack_error_invalid);
    test_simple_read_error("", 0 == mpack_expect_u64(&reader), mpack_error_invalid);
    test_simple_read_error("", 0 == mpack_expect_i8(&reader), mpack_error_invalid);
    test_simple_read_error("", 0 == mpack_expect_i16(&reader), mpack_error_invalid);
    test_simple_read_error("", 0 == mpack_expect_i32(&reader), mpack_error_invalid);
    test_simple_read_error("", 0 == mpack_expect_i64(&reader), mpack_error_invalid);
    test_simple_read_error("", 0.0f == mpack_expect_float(&reader), mpack_error_invalid);
    test_simple_read_error("", 0.0 == mpack_expect_double(&reader), mpack_error_invalid);
    test_simple_read_error("", 0.0f == mpack_expect_float_strict(&reader), mpack_error_invalid);
    test_simple_read_error("", 0.0 == mpack_expect_double_strict(&reader), mpack_error_invalid);
}

static void test_expect_data() {

    test_simple_read_cancel("\xa0", 0 == mpack_expect_str(&reader));

}

static void test_expect_compound() {

    // arrays
    test_simple_read_cancel("\x90", 0 == mpack_expect_array(&reader));
    test_simple_read_cancel("\x91", 1 == mpack_expect_array(&reader));
    test_simple_read_cancel("\x9f", 15 == mpack_expect_array(&reader));
    test_simple_read_cancel("\xdc\x00\x00", 0 == mpack_expect_array(&reader));
    test_simple_read_cancel("\xdc\x01\x00", 0x100 == mpack_expect_array(&reader));
    test_simple_read_cancel("\xdc\xff\xff", 0xffff == mpack_expect_array(&reader));
    test_simple_read_cancel("\xdd\x00\x00\x00\x00", 0 == mpack_expect_array(&reader));
    test_simple_read_cancel("\xdd\x00\x00\x01\x00", 0x100 == mpack_expect_array(&reader));
    test_simple_read_cancel("\xdd\x00\x01\x00\x00", 0x10000 == mpack_expect_array(&reader));
    test_simple_read_cancel("\xdd\xff\xff\xff\xff", UINT32_MAX == mpack_expect_array(&reader));

    test_simple_read_cancel("\x91", 1 == mpack_expect_array_range(&reader, 0, 1));
    test_simple_read_cancel("\x91", 1 == mpack_expect_array_range(&reader, 1, 1));
    test_simple_read_error("\x91", 2 == mpack_expect_array_range(&reader, 2, 2), mpack_error_type);
    test_simple_read_assert("\x91", mpack_expect_array_range(reader, 2, 1));
    test_simple_read_cancel("\x91", 1 == mpack_expect_array_max(&reader, 1));
    test_simple_read_error("\x91", 0 == mpack_expect_array_max(&reader, 0), mpack_error_type);

    test_simple_read_cancel("\x90", (mpack_expect_array_match(&reader, 0), true));
    test_simple_read_cancel("\x9f", (mpack_expect_array_match(&reader, 15), true));
    test_simple_read_cancel("\xdc\xff\xff", (mpack_expect_array_match(&reader, 0xffff), true));
    test_simple_read_cancel("\xdd\xff\xff\xff\xff", (mpack_expect_array_match(&reader, UINT32_MAX), true));

    // maps
    test_simple_read_cancel("\x80", 0 == mpack_expect_map(&reader));
    test_simple_read_cancel("\x81", 1 == mpack_expect_map(&reader));
    test_simple_read_cancel("\x8f", 15 == mpack_expect_map(&reader));
    test_simple_read_cancel("\xde\x00\x00", 0 == mpack_expect_map(&reader));
    test_simple_read_cancel("\xde\x01\x00", 0x100 == mpack_expect_map(&reader));
    test_simple_read_cancel("\xde\xff\xff", 0xffff == mpack_expect_map(&reader));
    test_simple_read_cancel("\xdf\x00\x00\x00\x00", 0 == mpack_expect_map(&reader));
    test_simple_read_cancel("\xdf\x00\x00\x01\x00", 0x100 == mpack_expect_map(&reader));
    test_simple_read_cancel("\xdf\x00\x01\x00\x00", 0x10000 == mpack_expect_map(&reader));
    test_simple_read_cancel("\xdf\xff\xff\xff\xff", UINT32_MAX == mpack_expect_map(&reader));

    test_simple_read_cancel("\x81", 1 == mpack_expect_map_range(&reader, 0, 1));
    test_simple_read_cancel("\x81", 1 == mpack_expect_map_range(&reader, 1, 1));
    test_simple_read_error("\x81", 2 == mpack_expect_map_range(&reader, 2, 2), mpack_error_type);
    test_simple_read_assert("\x81", mpack_expect_map_range(reader, 2, 1));
    test_simple_read_cancel("\x81", 1 == mpack_expect_map_max(&reader, 1));
    test_simple_read_error("\x81", 0 == mpack_expect_map_max(&reader, 0), mpack_error_type);

    test_simple_read_cancel("\x80", (mpack_expect_map_match(&reader, 0), true));
    test_simple_read_cancel("\x8f", (mpack_expect_map_match(&reader, 15), true));
    test_simple_read_cancel("\xde\xff\xff", (mpack_expect_map_match(&reader, 0xffff), true));
    test_simple_read_cancel("\xdf\xff\xff\xff\xff", (mpack_expect_map_match(&reader, UINT32_MAX), true));

}

void test_expect() {
    test_expect_example_read();

    // int/uint
    test_expect_uint_fixnum();
    test_expect_uint_signed_fixnum();
    test_expect_negative_fixnum();
    test_expect_uint();
    test_expect_uint_signed();
    test_expect_int();
    test_expect_uint_bounds();
    test_expect_int_bounds();
    test_expect_ints_dynamic_int();
    test_expect_int_range();
    test_expect_int_match();

    // other
    test_expect_misc();
    #if MPACK_READ_TRACKING
    test_expect_tracking();
    #endif
    test_expect_reals();
    test_expect_reals_range();
    test_expect_bad_type();
    test_expect_pre_error();

    // compound types
    test_expect_data();
    test_expect_compound();
}

#endif

