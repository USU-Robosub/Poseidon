// > list_i2c_data 0x4819C000 # for i2c-2
function list_i2c_data {
        readm $1 0
        readm $1 4
        readm $1 10
        readm $1 24
        readm $1 28
        readm $1 2C
        readm $1 30
        readm $1 34
        readm $1 38
        readm $1 3C
        readm $1 40
        readm $1 44
        readm $1 48
        readm $1 4C
        readm $1 90
        readm $1 94
        readm $1 98
        readm $1 9C
        readm $1 A4
        readm $1 A8
        readm $1 AC
        readm $1 B0
        readm $1 B4
        readm $1 B8
        readm $1 BC
        readm $1 C0
        readm $1 C4
        readm $1 C8
        readm $1 CC
        readm $1 D0
        readm $1 D4
}

function i2c2_enable {
        writem 0x44E00000  0 0
        writem 0x44E00000 44 2
}

function i2c2_disable {
        writem 0x44E00000 44 0
}

// > i2c2_data 4    # read  register 4
// > i2c2_data 3 1D # write register 3 w/value 0x1D
function i2c2_data {
        if [ -n "$2" ]
        then
                case $1 in
                         '1') writem 0x4819C0000  0 $2; ;;
                         '2') writem 0x4819C0000  4 $2; ;;
                         '3') writem 0x4819C0000 10 $2; ;;
                         '4') writem 0x4819C0000 24 $2; ;;
                         '5') writem 0x4819C0000 28 $2; ;;
                         '6') writem 0x4819C0000 2C $2; ;;
                         '7') writem 0x4819C0000 30 $2; ;;
                         '8') writem 0x4819C0000 34 $2; ;;
                         '9') writem 0x4819C0000 38 $2; ;;
                        '10') writem 0x4819C0000 3C $2; ;;
                        '11') writem 0x4819C0000 40 $2; ;;
                        '12') writem 0x4819C0000 44 $2; ;;
                        '13') writem 0x4819C0000 48 $2; ;;
                        '14') writem 0x4819C0000 4C $2; ;;
                        '15') writem 0x4819C0000 90 $2; ;;
                        '16') writem 0x4819C0000 94 $2; ;;
                        '17') writem 0x4819C0000 98 $2; ;;
                        '18') writem 0x4819C0000 9C $2; ;;
                        '19') writem 0x4819C0000 A4 $2; ;;
                        '20') writem 0x4819C0000 A8 $2; ;;
                        '21') writem 0x4819C0000 AC $2; ;;
                        '22') writem 0x4819C0000 B0 $2; ;;
                        '23') writem 0x4819C0000 B4 $2; ;;
                        '24') writem 0x4819C0000 B8 $2; ;;
                        '25') writem 0x4819C0000 BC $2; ;;
                        '26') writem 0x4819C0000 C0 $2; ;;
                        '27') writem 0x4819C0000 C4 $2; ;;
                        '28') writem 0x4819C0000 C8 $2; ;;
                        '29') writem 0x4819C0000 CC $2; ;;
                        '30') writem 0x4819C0000 D0 $2; ;;
                        '31') writem 0x4819C0000 D4 $2; ;;
                        *)
                        echo ERROR
                esac
        else
                case $1 in
                         '1') readm 0x4819C0000 0; ;;
                         '2') readm 0x4819C0000 4; ;;
                         '3') readm 0x4819C0000 10; ;;
                         '4') readm 0x4819C0000 24; ;;
                         '5') readm 0x4819C0000 28; ;;
                         '6') readm 0x4819C0000 2C; ;;
                         '7') readm 0x4819C0000 30; ;;
                         '8') readm 0x4819C0000 34; ;;
                         '9') readm 0x4819C0000 38; ;;
                        '10') readm 0x4819C0000 3C; ;;
                        '11') readm 0x4819C0000 40; ;;
                        '12') readm 0x4819C0000 44; ;;
                        '13') readm 0x4819C0000 48; ;;
                        '14') readm 0x4819C0000 4C; ;;
                        '15') readm 0x4819C0000 90; ;;
                        '16') readm 0x4819C0000 94; ;;
                        '17') readm 0x4819C0000 98; ;;
                        '18') readm 0x4819C0000 9C; ;;
                        '19') readm 0x4819C0000 A4; ;;
                        '20') readm 0x4819C0000 A8; ;;
                        '21') readm 0x4819C0000 AC; ;;
                        '22') readm 0x4819C0000 B0; ;;
                        '23') readm 0x4819C0000 B4; ;;
                        '24') readm 0x4819C0000 B8; ;;
                        '25') readm 0x4819C0000 BC; ;;
                        '26') readm 0x4819C0000 C0; ;;
                        '27') readm 0x4819C0000 C4; ;;
                        '28') readm 0x4819C0000 C8; ;;
                        '29') readm 0x4819C0000 CC; ;;
                        '30') readm 0x4819C0000 D0; ;;
                        '31') readm 0x4819C0000 D4; ;;
                        *)
                        echo ERROR
                esac
        fi
}
