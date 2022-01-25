
namespace registry {

template <typename Tag, typename T>
inline RegistryType<T>& getRegistry() {
  static RegistryType<T> reg;
  return reg;
}

template <typename Tag, typename T, typename ObjT>
Registrar<Tag, T, ObjT>::Registrar() {
  auto& reg = getRegistry<Tag, T>();
  index = reg.size();
  reg.emplace_back(T::construct());
}

template <typename Tag, typename T, typename ObjT>
IndexType const Type<Tag, T, ObjT>::idx = Registrar<Tag, T, ObjT>().index;

template <typename Tag, typename T>
inline IndexType getObjIdx(IndexType idx) {
  return getRegistry<Tag, T>().at(idx);
}

template <typename Tag, typename T, typename ObjT>
inline IndexType makeObjIdx() {
  return Type<Tag, T, ObjT>::idx;
}

} /* end namespace registry */
