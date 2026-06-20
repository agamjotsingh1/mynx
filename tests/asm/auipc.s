_start:
    auipc t0, 0
    auipc t1, 1
    auipc t2, 0xFFFFF

end_loop:
    j end_loop