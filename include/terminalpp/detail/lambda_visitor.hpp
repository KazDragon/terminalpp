#pragma once

namespace terminalpp { namespace detail {

template <typename ReturnType, typename... Lambdas>
struct lambda_visitor;

template <typename ReturnType, typename Lambda1, typename... Lambdas>
struct lambda_visitor< ReturnType, Lambda1 , Lambdas...>
  : public lambda_visitor<ReturnType, Lambdas...>, public Lambda1 {

    using Lambda1::operator();
    using lambda_visitor< ReturnType , Lambdas...>::operator();
    lambda_visitor(Lambda1 l1, Lambdas... lambdas)
      : Lambda1(l1), lambda_visitor< ReturnType , Lambdas...> (lambdas...)
    {}
};


template <typename ReturnType, typename Lambda1>
struct lambda_visitor<ReturnType, Lambda1>
  : public boost::static_visitor<ReturnType>, public Lambda1 {

    using Lambda1::operator();
    lambda_visitor(Lambda1 l1)
      : boost::static_visitor<ReturnType>(), Lambda1(l1)
    {}
};


template <typename ReturnType>
struct lambda_visitor<ReturnType>
  : public boost::static_visitor<ReturnType> {

    lambda_visitor() : boost::static_visitor<ReturnType>() {}
};

template <typename ReturnType = void, typename... Lambdas>
lambda_visitor<ReturnType, Lambdas...> make_lambda_visitor(Lambdas... lambdas) {
    return { lambdas... };
}

}}

