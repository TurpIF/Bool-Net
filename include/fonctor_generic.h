#ifndef __FONCTOR_GENERIC_H__
#define __FONCTOR_GENERIC_H__

template <typename fonctorN, std::size_t N>
struct fonctor_traits
{
};

template <typename F1, typename F2>
struct sum2
{
    typedef typename F1::traits traits;
    typedef typename traits::return_type return_type;
    typedef typename traits::argument_type argument_type;

    sum2(F1 f1 = F1(), F2 f2 = F2()):
        _f1(f1),
        _f2(f2)
    {
    }

    inline return_type operator()(argument_type const & s)
    {
        return _f1.operator()(s) + _f2.operator()(s);
    }

    private:
    F1 _f1;
    F2 _f2;
};

template <typename F1, typename F2, typename F3>
struct sum3
{
    typedef typename F1::traits traits;
    typedef typename traits::return_type return_type;
    typedef typename traits::argument_type argument_type;

    sum3(F1 f1 = F1(), F2 f2 = F2(), F3 f3 = F3()):
        _f1(f1),
        _f2(f2),
        _f3(f3)
    {
    }

    inline return_type operator()(argument_type const & s)
    {
        return _f1.operator()(s) + _f2.operator()(s) + _f3.operator()(s);
    }

    private:
    F1 _f1;
    F2 _f2;
    F3 _f3;
};

template <typename F1, typename F2, typename F3, typename F4>
struct sum4
{
    typedef typename F1::traits traits;
    typedef typename traits::return_type return_type;
    typedef typename traits::argument_type argument_type;

    sum4(F1 f1 = F1(), F2 f2 = F2(), F3 f3 = F3(), F4 f4 = F4()):
        _f1(f1),
        _f2(f2),
        _f3(f3),
        _f4(f4)
    {
    }

    inline return_type operator()(argument_type const & s)
    {
        return _f1.operator()(s) + _f2.operator()(s) + _f3.operator()(s) + _f4.operator()(s);
    }

    private:
    F1 _f1;
    F2 _f2;
    F3 _f3;
    F4 _f4;
};

template <typename F1, typename F2, typename F3, typename F4, typename F5>
struct sum5
{
    typedef typename F1::traits traits;
    typedef typename traits::return_type return_type;
    typedef typename traits::argument_type argument_type;

    sum5(F1 f1 = F1(), F2 f2 = F2(), F3 f3 = F3(), F4 f4 = F4(), F5 f5 = F5()):
        _f1(f1),
        _f2(f2),
        _f3(f3),
        _f4(f4),
        _f5(f5)
    {
    }

    inline return_type operator()(argument_type const & s)
    {
        return _f1.operator()(s) + _f2.operator()(s) + _f3.operator()(s) + _f4.operator()(s) + _f5.operator()(s);
    }

    private:
    F1 _f1;
    F2 _f2;
    F3 _f3;
    F4 _f4;
    F5 _f5;
};

template <typename Rule>
struct delay
{
    typedef typename Rule::traits traits;
    typedef typename traits::return_type return_type;
    typedef typename traits::argument_type argument_type;

    delay(std::size_t delay, bool reset_if_ready = false, Rule const & e = Rule()):
        _reset_if_ready(reset_if_ready),
        _delay(delay),
        _current_time(0),
        _effect(e)
    {
    }

    void update()
    {
        _current_time++;
    }

    void reset()
    {
        _current_time = 0;
    }

    bool ready() const
    {
        return _current_time >= _delay;
    }

    inline return_type operator()(argument_type const & s)
    {
        update();
        if(_current_time >= _delay)
        {
            if(_reset_if_ready)
                reset();
            return _effect.operator()(s);
        }
        return traits::ReturnNothing;
    }

    private:
    const bool _reset_if_ready;
    const std::size_t _delay;
    std::size_t _current_time;
    Rule _effect;
};

template <typename Rule>
delay<Rule> make_delay(std::size_t time, bool reset_if_ready = false, Rule const & e = Rule())
{ return delay<Rule>(time, reset_if_ready, e); }

template <typename F1, typename F2>
sum2<F1, F2> make_sum(F1 const & f1 = F1(), F2 const & f2 = F2())
{ return sum2<F1, F2>(f1, f2); }

template <typename F1, typename F2, typename F3>
sum3<F1, F2, F3> make_sum(F1 const & f1 = F1(), F2 const & f2 = F2(), F3 const & f3 = F3())
{ return sum3<F1, F2, F3>(f1, f2, f3); }

template <typename F1, typename F2, typename F3, typename F4>
sum4<F1, F2, F3, F4> make_sum(F1 const & f1 = F1(), F2 const & f2 = F2(), F3 const & f3 = F3(), F4 const & f4 = F4())
{ return sum4<F1, F2, F3, F4>(f1, f2, f3, f4); }

template <typename F1, typename F2, typename F3, typename F4, typename F5>
sum5<F1, F2, F3, F4, F5> make_sum(F1 const & f1 = F1(), F2 const & f2 = F2(), F3 const & f3 = F3(), F4 const & f4 = F4(), F5 const & f5 = F5())
{ return sum5<F1, F2, F3, F4, F5>(f1, f2, f3, f4, f5); }

#endif
