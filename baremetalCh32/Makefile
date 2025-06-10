TOOLCHAIN_URL  := https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/download/v14.2.0-3/xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz
TOOLCHAIN_TAR  := $(notdir $(TOOLCHAIN_URL))
TOOLCHAIN_TEMP := xpack-riscv-none-elf-gcc-14.2.0-3

toolchain:
	@echo "==> Downloading RISC-V toolchain..."
	@wget -cq $(TOOLCHAIN_URL)
	@echo "==> Extracting toolchain..."
	@tar -xf $(TOOLCHAIN_TAR)
	@mv -f $(TOOLCHAIN_TEMP) $@
	@rm $(TOOLCHAIN_TAR)
	@echo "==> Toolchain ready in ./$@"
