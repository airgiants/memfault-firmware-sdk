"""
Small wrapper to hook the Memfault build id script into platform IO.
"""

Import("env")

env.AddPostAction(
    "$BUILD_DIR/${PROGNAME}.elf",
    env.VerboseAction(
        " ".join(
            [
                "$PYTHONEXE",
                "$PROJECT_DIR/src/memfault/memfault-firmware-sdk/scripts/fw_build_id.py",
                "$BUILD_DIR/${PROGNAME}.elf",
            ]
        ),
        "Adding build id to $BUILD_DIR/${PROGNAME}.elf",
    ),
)
