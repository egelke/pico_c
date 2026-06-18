#ifndef ERROR_H
#define ERROR_H

#define EGK_OK                          (0)
#define EGK_ERROR_BASE                  (-650838016) // 1101 1001 0011 0101 0000 0000 0000 0000
#define EGK_ERROR_GENERIC               (EGK_ERROR_BASE -1)
#define EGK_ERROR_IO                    (EGK_ERROR_BASE -2)
#define EGK_ERROR_CRC                   (EGK_ERROR_BASE -3)

#endif /* ERROR_H */