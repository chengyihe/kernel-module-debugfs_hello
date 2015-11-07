obj-m += debugfs_hello.o

all:
	make -C ${KERNEL_PATH} M=$(PWD) modules

clean:
	make -C $(KERNEL_PATH) M=$(PWD) clean
