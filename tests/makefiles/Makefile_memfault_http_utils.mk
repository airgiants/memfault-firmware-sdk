COMPONENT_NAME=memfault_http_client_util

SRC_FILES = \
  $(MFLT_COMPONENTS_DIR)/http/src/memfault_http_utils.c \

MOCK_AND_FAKE_SRC_FILES += \
  $(MFLT_TEST_FAKE_DIR)/fake_memfault_platform_debug_log.c \
  $(MFLT_TEST_STUB_DIR)/stub_memfault_log_save.c \


TEST_SRC_FILES = \
  $(MFLT_TEST_SRC_DIR)/test_memfault_http_utils.cpp \
  $(MOCK_AND_FAKE_SRC_FILES)

include $(CPPUTEST_MAKFILE_INFRA)
