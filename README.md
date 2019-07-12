# sgx-enable

Enable software-controlled SGX persistently.
The programs requires root to write to `/sys/firmware/efi`.
After execution a boot might be required.

Build with:


```console
make
```

Then just run the program as root

```
./sgx-enable
```
