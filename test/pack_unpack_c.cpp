#include <msgpack.h>
#include <gtest/gtest.h>
#include <stdio.h>

TEST(pack, num)
{
    msgpack_sbuffer* sbuf = msgpack_sbuffer_new();
    msgpack_packer* pk = msgpack_packer_new(sbuf, msgpack_sbuffer_write);

    EXPECT_EQ(0, msgpack_pack_int(pk, 1));

    msgpack_sbuffer_free(sbuf);
    msgpack_packer_free(pk);
}


TEST(pack, array)
{
    msgpack_sbuffer* sbuf = msgpack_sbuffer_new();
    msgpack_packer* pk = msgpack_packer_new(sbuf, msgpack_sbuffer_write);

    EXPECT_EQ(0, msgpack_pack_array(pk, 3));
    EXPECT_EQ(0, msgpack_pack_int(pk, 1));
    EXPECT_EQ(0, msgpack_pack_int(pk, 2));
    EXPECT_EQ(0, msgpack_pack_int(pk, 3));

    msgpack_sbuffer_free(sbuf);
    msgpack_packer_free(pk);
}


TEST(unpack, sequence)
{
    msgpack_sbuffer* sbuf = msgpack_sbuffer_new();
    msgpack_packer* pk = msgpack_packer_new(sbuf, msgpack_sbuffer_write);

    EXPECT_EQ(0, msgpack_pack_int(pk, 1));
    EXPECT_EQ(0, msgpack_pack_int(pk, 2));
    EXPECT_EQ(0, msgpack_pack_int(pk, 3));

    msgpack_packer_free(pk);

    msgpack_unpack_return success;
    size_t offset = 0;

    msgpack_unpacked msg;
    msgpack_unpacked_init(&msg);

    success = msgpack_unpack_next(&msg, sbuf->data, sbuf->size, &offset);
    EXPECT_EQ(MSGPACK_UNPACK_SUCCESS, success);
    EXPECT_EQ(MSGPACK_OBJECT_POSITIVE_INTEGER, msg.data.type);
    EXPECT_EQ(1u, msg.data.via.u64);

    success = msgpack_unpack_next(&msg, sbuf->data, sbuf->size, &offset);
    EXPECT_EQ(MSGPACK_UNPACK_SUCCESS, success);
    EXPECT_EQ(MSGPACK_OBJECT_POSITIVE_INTEGER, msg.data.type);
    EXPECT_EQ(2u, msg.data.via.u64);

    success = msgpack_unpack_next(&msg, sbuf->data, sbuf->size, &offset);
    EXPECT_EQ(MSGPACK_UNPACK_SUCCESS, success);
    EXPECT_EQ(MSGPACK_OBJECT_POSITIVE_INTEGER, msg.data.type);
    EXPECT_EQ(3u, msg.data.via.u64);

    success = msgpack_unpack_next(&msg, sbuf->data, sbuf->size, &offset);
    EXPECT_EQ(MSGPACK_UNPACK_CONTINUE, success);

    msgpack_sbuffer_free(sbuf);
    msgpack_unpacked_destroy(&msg);
}

