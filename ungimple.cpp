int main(int argc, char **argv = 0) {
    void *goto_ptr = 0;
    main(
        main(({
            goto_ptr = &&_1;
            goto *goto_ptr;
            _1:
            0;
        })) +
        main(({
            goto_ptr = &&_2;
            goto *goto_ptr;
            _2:
            0;
        }))
    );
}
