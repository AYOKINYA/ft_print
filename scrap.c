ptr = ft_abs(ptr);
print_len = ft_len(ptr);

printf("precision_len : %d", precision_len);
printf("width : %d", width);
printf("print_len : %d", print_len);

 if (precision_len != 0)
                {
                    while (width > precision_len + 1)
                    {
                        ft_putchar('k');
                        --width;
                    }
                }

if (precision_len != 0 && left_align != 1)
                {   
                    if (print_len > precision_len)
                        ft_pad_left_blank(width, print_len, left_align, zero_padding);
                    else
                        ft_pad_left_blank(width, precision_len + 1, left_align, zero_padding);
                }