
#ifndef __PORT_H
#define __PORT_H

    #include "types.h"


    class Port
    {
        protected:
            Port(uint16_t portnumber);
            // FIXME: Must be virtual (currently isnt because the kernel has no memory management yet)
            ~Port();
            uint16_t portnumber;
    };

    
    class Port8 : public Port
    {
        public:
            Port8(uint16_t portnumber);
            ~Port8();

            virtual uint8_t read();
            virtual void write(uint8_t data);

        protected:
            static inline uint8_t read8(uint16_t _port)
            {
                uint8_t result;
                __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
                return result;
            }

            static inline void write8(uint16_t _port, uint8_t _data)
            {
                __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
            }
    };



    class Port8Slow : public Port8
    {
        public:
            Port8Slow(uint16_t portnumber);
            ~Port8Slow();

            virtual void write(uint8_t data);
        protected:
            static inline void write8Slow(uint16_t _port, uint8_t _data)
            {
                __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port));
            }

    };



    class Port16 : public Port
    {
        public:
            Port16(uint16_t portnumber);
            ~Port16();

            virtual uint16_t read();
            virtual void write(uint16_t data);

        protected:
            static inline uint16_t read16(uint16_t _port)
            {
                uint16_t result;
                __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
                return result;
            }

            static inline void write16(uint16_t _port, uint16_t _data)
            {
                __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
            }
    };



    class Port32 : public Port
    {
        public:
            Port32(uint16_t portnumber);
            ~Port32();

            virtual uint32_t read();
            virtual void write(uint32_t data);

        protected:
            static inline uint32_t read32(uint16_t _port)
            {
                uint32_t result;
                __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
                return result;
            }

            static inline void write32(uint16_t _port, uint32_t _data)
            {
                __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
            }
    };




#endif
