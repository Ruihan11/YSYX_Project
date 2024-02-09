# @echo "Write this Makefile by your self."
# make-----
# verilator -Wno-fatal vsrc/top.v csrc/tb_top_wave.cpp --top-module top --cc --trace --exe
# make -C obj_dir -f Vtop.mk Vtop
# sim------
# ./obj_dir/Vtop 
# wave-----
# gtkwave wave.vcd
############################################

moduleName = LFSR

VSRC = vsrc/$(moduleName).v

# without wave
# CSRC = csrc/tb_$(moduleName).cpp
# with wave
CSRC = csrc/tb_$(moduleName)_wave.cpp

all:
	make clean
	verilator -Wno-fatal $(VSRC) $(CSRC) --top-module $(moduleName) --cc --trace --exe
	make -C obj_dir -f V$(moduleName).mk V$(moduleName)
 
sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	
	./obj_dir/V$(moduleName)
	
 
wave:
	gtkwave wave.vcd


.PHONY:clean
clean:
	rm -rf obj_dir wave.vcd	