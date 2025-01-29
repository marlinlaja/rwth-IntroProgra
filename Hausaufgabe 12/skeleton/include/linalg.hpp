/**
 * \file linalg.hpp
 */

#pragma once

#include <cassert>
#include <ostream>
#include <utility>

namespace linalg {

/**
 * \class TrackedViewable
 * \brief Eine Basisklasse für Objekte, von den "Views" genommen können.
 * \details "Views" sind Objekte, die es ermöglichen, Teile eines `Vector`s oder
 * einer `Matrix` anzusehen, ohne dass die deren Einträge kopiert werden müssen. 
 * Wenn "Views" konstruiert oder dekonstruiert werden, 
 * sollen sie den TrackedViewable, den sie ansehen,
 * informieren mittels \ref increment_live_views bzw. \ref decrement_live_views.
 *
 * ConstVectorView, genau wie die `const_interator` Typen der
 * Standardbibliothek, erlauben keine Modifizierung des angesehenen `Vector`s
 * bzw. der angesehenen `Matrix`.
 *
 * Im Vergleich erlaubt VectorView, genau wie die `iterator` Typen der
 * Standardbibliothek, die Modifizierung des angesehenen `Vector`s bzw. der
 * angesehenen `Matrix`.
 *
 * Diese Klasse ist schon implementiert.
 *
 * Siehe:
 *  - Vector::view
 *  - Vector::cview
 *  - Matrix::rowview oder Matrix::colview
 *  - Matrix::crowview oder Matrix::ccolview
 */
class TrackedViewable {
  /**
   * \brief `view_count` ist die Anzahl von existierende "Views" dieses Objekts.
   */
  mutable int view_count = 0;

public:
  /**
   * \brief Inkrementiert \ref view_count um eins. Diese soll immer wenn ein
   * "View" erzeugt wird aufgerufen werden.
   */
  void increment_live_views() const { view_count++; };

  /**
   * \brief Dekrementiert \ref view_count um eins. Diese soll immer wenn ein
   * "View" gelöscht wird aufgerufen werden.
   */
  void decrement_live_views() const { view_count--; };

  /**
   * \brief Ergibt `true` genau dann, wenn keine "Views" dieses Objekts noch
   * existieren. Diese Bedingung soll immer wenn dieses Objekts gelöscht wird
   * geprüft werden.
   */
  bool is_safe_to_destroy() const { return view_count == 0; };

  /**
   * \brief Ergibt `view_count`.
   */
  int live_view_count() const { return view_count; };
};

/**
  \class VectorLike
  \brief Eine Basisklasse für Objekte, die zu einem Vektor änlich sind.
  \details `VectorLike` Objekte beschreiben Vektoren in \f(\mathbb R^n\f). Die
  `VectorLike` Schnittstelle erlaubt Lesezugriff auf die Einträgen eines
  Vektors.
 */
class VectorLike {

protected:
  /**
   * \brief Prüft ob der Index `i` erlaubt ist.
   * \details Zum Beispiel, ein Vektor mit fünf Einträge soll nur \f(0\leq
   * i<5\f) erlauben.
   */
  bool check_bounds(int i) const;

public:
  virtual ~VectorLike();

  /**
   * \brief Ergibt die Länge dieses `VectorLike`s.
   */
  virtual int size() const = 0;

  /**
   * \brief Ergibt den Wert zum Index `i` in diesem VectorLike.
   */
  virtual double at(int i) const = 0;
};

/**
  \class MutableVectorLike
  \brief Eine Basisklasse für Objekte, die zu einem Vektor änlich sind.
  \details `VectorLike` Objekte beschreiben Vektoren in \f(\mathbb R^n\f). Die
  `VectorLike` Schnittstelle erlaubt sowohl Zugang zu den Einträgen eines
  konstanten Vektors als auch Zuweisung den Einträgen eines variablen Vektors.
 */
class MutableVectorLike : public VectorLike {
public:
  // assignment "operators" in place!
  using VectorLike::at;

  /**
   * \brief Ergibt eine Referenz zum `i`-ten Wert dieses `VectorLikes`.
   */
  virtual double &at(int i) = 0;

  /**
   * \brief Weist die Werte des Vektors \f(u\f) zu den entsprechenden Werte
   * dieses `VectorLike`s \f(v\f) zu.
   * \param[in] u Der `VektorLike`, der zu \f(v\f) zugewiesen wird.
   * \details Fürht die Zuweisung \f[v_i = u_i\f] aus.
   */
  void assign_other(VectorLike const &u);

  /**
   * \brief Addiert die Werte des Vektors \f(u\f) zu den entsprechenden Werte
   * dieses `VectorLike`s \f(v\f).
   * \param[in] u Der `VektorLike`, der zu \f(v\f) addiert wird.
   * \details Fürht die Zuweisung \f[v_i = v_i+u_i\f] aus.
   */
  void add_assign_other(VectorLike const &u);
  /**
   * \brief Subtrahiert die Werte des Vektors \f(u\f) von den entsprechenden
   * Werte dieses `VectorLike`s \f(v\f).
   * \param[in] u Der `VektorLike`, der von \f(v\f) subtrahiert wird.
   * \details Fürht die Zuweisung \f[v_i = v_i-u_i\f] aus.
   */
  void subtract_assign_other(VectorLike const &u);

  /**
   *\brief Skaliert die Werte dieses `VectorLike`s \f(v\f) um \f(a\f).
   *\param[in] a Der Wert, von dem die Werte dieses `VectorLike`s skaliert wird.
   *\details Fürht die Zuweisung \f[v_i = a*v_i\f] aus.
   */
  void assign_scalar_multiply(double a);
};

/**
 * \class ConstVectorView
 * \brief Erlaubt Lesezugriff auf "slices" oder "views" von Vektoren oder
 * Matrixen, ohne dass Werte hin und her kopiert werden müssen.
 *
 * \details Mögliche Anwendungen dieser Klasse sind, zum Beispiel:
 *   - Lesezugriff auf die letzten 10 Einträge von einem \ref Vector
 *   - Lesezugriff auf eine bestimmte Spalte oder Zeile von einer \ref Matrix
 *
 * Alle ConstVectorView haben eine Variable \ref viewed, die eine \ref
 * TrackedViewable referenziert. Wenn ein VectorView konstruiert oder
 * dekonstruiert wird, muss \ref TrackedViewable::increment_live_views bzw. \ref
 * TrackedViewable::decrement_live_views aufgerufen werden.
 *
 * Ein ConstVectorView ist _nicht_ dafür verantwortlich, etwas mit `delete []`
 * zu deallozieren!
 */
class ConstVectorView : public VectorLike {
  /**
   * \brief Das speicher-besitzende Objekt, zu dem dieser ConstVectorView Zugang
   * hat.
   */
  TrackedViewable const &viewed;

  /**
   * \brief Ein Zeiger auf den ersten Eintrag dieses ConstVectorViews
   */
  double const *const view_start;

  /**
   * \brief Die Anzahl von Einträge in diesem ConstVectorView
   */
  int length;

  /**
   * \brief Die Distanz zwischen den Zeigern auf zwei aufeinanderfolgende
   * Einträge dieses ConstVectorView.
   * \details Zum Beispiel, wenn dieser ConstVectorView auf ein \ref Vector
   * Zugang bietet, ist `stride` gleich 1. Wenn dieser ConstVectorView eine
   * Spalte einer \ref Matrix darstellt, wird `stride` die Länge einer Zeile der
   * Matrix entsprechen.
   */
  int stride;

public:
  /**
   * \brief Konstruiert einen neuen ConstVectorView, der Lesezugriff auf
   * `t_viewed` hat.
   * \param[in] t_viewed Der \ref TrackedViewable, worauf dieser Lesezugriff
   * hat.
   * \param[in] t_start Ein Zieger zum ersten Wert in diesem ConstVectorView
   * \param[in] t_length Die Anzahl der Elemente in diesem ConstVectorView
   * \param[in] t_stride Die Distanz zwischen zwischen den Zeigern zu zwei
   * aufeinanderfolgende Einträge dieses `ConstVectorView`s.
   * \details Dieser Konstrutor muss `viewed.increment_live_views()` aufrufen.
   */
  ConstVectorView(TrackedViewable const &t_viewed, double const *t_start,
                  int t_length, int t_stride);

  /**
   * \brief Konstruiert einen neuen ConstVectorView mit \ref stride gleich 1,
   * der Lesezugriff auf `t_viewed` hat.
   * \param[in] t_viewed Der \ref TrackedViewable, worauf dieser Lesezugriff
   * hat.
   * \param[in] t_start Ein Zieger zum ersten Wert in diesem ConstVectorView.
   * \param[in] t_length Die Anzahl der Elemente in diesem ConstVectorView.
   * \details Dieser Konstrutor muss entweder `viewed.increment_live_views()`
   * aufrufen oder den anderen Konstruktor nutzen.
   */
  ConstVectorView(TrackedViewable const &t_viewed, double const *t_start,
                  int t_length);

  /**
   * \brief Dekonstruiert dieses `ConstVektorView`s.
   * \details Muss \ref viewed informieren, dass dieser View dekronstruiert
   * wird.
   */
  ~ConstVectorView();

  int size() const override;
  double at(int i) const override;

  /**
   * \brief Ergibt einen View auf ein Teil dieses `ConstVectorView`s.
   * \param[in] start Der Index, wo der neue ConstVectorView anfängt.
   * \param[in] length Die Länge des neuen `ConstVectorView`s.
   * \returns Einen ConstVectorVew von den Indizes \f([start, length)\f) dieses
   * `ConstVectorView`s
   */
  ConstVectorView const cview(int start, int length) const;
};

/**
 * \class VectorView
 * \brief Erlaubt Zugang zu "slices" oder "views" von Vektoren
 * oder Matrixen, ohne dass Werte hin und her kopiert werden müssen.
 * \details Mögliche Anwendungen dieser Klasse sind, zum Beispiel:
 *   - Zugang den letzten 10 Einträge von einem \ref Vector
 *   - Zugang einer bestimmten Spalte oder Zeile von einer \ref Matrix
 *
 * Alle VectorViews haben eine Variable \ref viewed, die eine \ref
 * TrackedViewable referenziert. Wenn ein VectorView konstruiert oder
 * dekonstruiert wird, muss \ref TrackedViewable::increment_live_views bzw. \ref
 * TrackedViewable::decrement_live_views aufgerufen werden.
 *
 * Ein VectorView ist _nicht_ dafür verantwortlich, etwas mit `delete []` zu
 * deallozieren!
 */
class VectorView : public MutableVectorLike {
  /**
   * \brief Das speicher-besitzende Objekt, zu dem dieser VectorView Zugang hat.
   */
  TrackedViewable const &viewed;

  /**
   * \brief Ein Zeiger auf den ersten Eintrag dieses Views
   */
  double *const view_start;

  /**
   * \brief Die Anzahl von Einträge in diesem VectorView
   */
  int length;

  /**
   * \brief Die Distanz zwischen den Zeigern auf zwei aufeinanderfolgende
   * Einträge dieses VectorViews.
   * \details Zum Beispiel, wenn dieser VectorView auf ein \ref Vector Zugang
   * bietet, ist `stride` gleich 1. Wenn dieser VectorView eine Spalte einer
   * \ref Matrix darstellt, wird `stride` die Länge einer Zeile der Matrix
   * entsprechen.
   */
  int stride;

public:
  /**
   * \brief Konstruiert einen neuen VectorView, der sowohl Lese- als auch
   * Schreibezugriff auf `t_viewed` hat.
   * \param[in] t_viewed Der \ref TrackedViewable,
   * worauf dieser Lesezugriff hat.
   * \param[in] t_start Ein Zieger zum ersten Wert in diesem VectorView.
   * \param[in] t_length Die Anzahl der Elemente in diesem VectorView
   * \param[in] t_stride Die Distanz zwischen zwischen den Zeigern
   * zu zwei aufeinanderfolgende Einträge dieses `VectorView`s.
   * \details Dieser Konstrutor muss `viewed.increment_live_views()` aufrufen.
   */
  VectorView(TrackedViewable const &t_viewed, double *t_start, int t_length,
             int t_stride);

  /**
   * \brief Konstruiert einen neuen VectorView mit \ref stride gleich 1,
   * der sowohl Lese- als auch Schreibezugriff auf `t_viewed` hat.
   * \param[in] t_viewed Der \ref TrackedViewable, worauf dieser Lesezugriff
   * hat.
   * \param[in] t_start Ein Zieger zum ersten Wert in diesem VectorView.
   * \param[in] t_length Die Anzahl der Elemente in diesem VectorView.
   * \details Dieser Konstrutor muss entweder `viewed.increment_live_views()`
   * aufrufen oder den anderen Konstruktor nutzen.
   */
  VectorView(TrackedViewable const &t_viewed, double *t_start, int t_length);
  ~VectorView();

  int size() const override;
  double at(int i) const override;
  double &at(int i) override;

  /**
   * \brief Ergibt einen konstanten View auf ein Teil dieses `VectorView`s.
   * \param[in] start Der Index, wo der neue ConstVectorView anfängt.
   * \param[in] length Die Länge des neuen `ConstVectorView`s.
   * \returns Einen ConstVectorView von den Indizes \f([start, length)\f) dieses
   * `VectorView`s
   */
  ConstVectorView cview(int start, int length) const;

  /**
   * \brief Ergibt einen View auf ein Teil dieses `VectorView`s.
   * \param[in] start Der Index, wo der neue VectorView anfängt.
   * \param[in] length Die Länge des neuen `VectorView`s.
   * \returns Einen VectorView von den Indizes \f([start, length)\f) dieses
   * `VectorView`s
   */
  VectorView view(int start, int length);
};

/**
 * \class Vector
 * \brief Ein Vektor in \f(\mathbb R^n\f).
 * \details Diese Klasse implementiert die VektorLike Schnittstelle und besitzt
 * ein Zeiger \ref data auf \ref length `double`-Werten. \ref data wird mit `new
 * []` alloziert und mit `delete []` dealloziert!
 */
class Vector : public MutableVectorLike, public TrackedViewable {
  /**
   * \brief Ein Zeiger auf den Speicher dieser Vektor besitzt und verwaltet.
   */
  double *data;
  /**
   * \brief Die Länge dieses Vektors.
   */
  int length;

public:
  /**
   * \brief Konstruiert einen Vektor mit Länge `length`.
   * \param[in] length Die Anzahl von `double`-Werten, die mit `new []`
   * alloziert werden soll.
   */
  Vector(int length);

  /**
   * \brief Konstruiert einen Vektor, welcher eine Kopie von `t_other` ist.
   */
  Vector(linalg::VectorLike const &t_other);

  /**
   * \brief Dekonstruiert diesen Vektor.
   * \details Prüft erst, ob es noch existierende Views von diesem Vektor gibt.
   * In dem Fall wird eine Warnung zum `std::cout` gegeben.
   */
  ~Vector();

  // implement methods from VectorLike
  int size() const override;
  double at(int i) const override;
  double &at(int i) override;

  /**
   * \brief Ergibt einen konstanten View auf ein Teil dieses `Vector`s.
   * \param[in] start Der Index, wo der neue ConstVectorView anfängt.
   * \param[in] length Die Länge des neuen `ConstVectorView`s.
   * \returns Einen ConstVectorView von den Indizes \f([start, length)\f) dieses
   * `Vector`s
   */
  ConstVectorView cview(int start, int length) const;

  /**
   * \brief Ergibt einen View auf ein Teil dieses `Vector`s.
   * \param[in] start Der Index, wo der neue VectorView anfängt.
   * \param[in] length Die Länge des neuen `VectorView`s.
   * \returns Einen VectorView von den Indizes \f([start, length)\f) dieses
   * `Vector`s
   */
  VectorView view(int start, int length);
};

/**
 * \class Matrix
 * \brief Ein Vektor in \f(\mathbb R^{m\times n}\f).
 * \details Diese Klasse besitzt einen Zeiger \ref data auf `dims.first *
 * dims.second` `double`-Werten. \ref data wird mit `new
 * []` alloziert und mit `delete []` dealloziert! Zugang auf diese Werte ist mit
 * \ref Matrix::at möglich.
 */
class Matrix : public TrackedViewable {
  /**
   * \brief Ein Zeiger auf den Speicher diese Matrix besitzt und verwaltet.
   */
  double *data;

  /**
   * \brief Die Dimensionen dieser Matrix.
   * \details `dims.first` entspricht die Anzahl der Zeilen dieser Matrix, und
   * `dims.second` entspricht die Anzahl der Spalten.
   */
  std::pair<int, int> dims;

  /**
   * \brief Prüft, ob `i` ein gültiger Index einer Zeile dieser Matrix ist.
   */
  bool check_row_bounds(int i) const;

  /**
   * \brief Prüft, ob `j` ein gültiger Index einer Spalte dieser Matrix ist.
   */
  bool check_col_bounds(int j) const;

  /**
   * \brief Pruft, ob `(i, j)` ein gültiger Index eines Eintrags dieser Matrix
   * ist.
   */
  bool check_bounds(int i, int j) const;

public:
  /**
   * \brief Konstruiert eine Matrix mit Dimensionen `dims`.
   * \param[in] dims Die Dimensionen dieser Matrix. `dims.first * dims.second`
   * `double`-Werte werden mit new [] alloziert.
   */
  Matrix(std::pair<int, int> dims);

  /**
   * \brief Konstruiert eine Matrix mit Dimensionen \f(M\times N\f).
   */
  Matrix(int M, int N);

  /**
   * \brief Konstruiert eine Matrix, welche eine Kopie von `t_other` ist.
   */
  Matrix(Matrix const &t_other);

  /**
   * \brief Dekonstruiert diese Matrix.
   * \details Prüft erst, ob es noch existierende Views von dieser Matrix gibt.
   * In dem Fall wird eine Warnung zum `std::cout` gegeben.
   */
  ~Matrix();

  /**
   * \brief Ergibt die Dimensionen dieser Matrix als `std::pair`.
   */
  std::pair<int, int> size() const;

  /**
   * \brief Ergibt den Wert zum Index `(i, j)` in dieser Matrix.
   */
  double at(int i, int j) const;

  /**
   * \brief Ergibt eine Referenz zum Wert zum Index `(i, j)` in dieser Matrix.
   */
  double &at(int i, int j);

  /**
   * \brief Ergibt einen ConstVectorView auf eine Zeile dieser Matrix.
   * \param[in] i Der Index der Zeile, von der einen View genommen wird.
   * \returns Einen ConstVectorVew von den Indizes \f([0, M)\f) in Zeile `i`
   * dieser Matrix.
   */
  ConstVectorView crowview(int i) const;

  /**
   * \brief Ergibt einen VectorView auf eine Zeile dieser Matrix.
   * \param[in] i Der Index der Zeile, von der einen View genommen wird.
   * \returns Einen VectorView von den Indizes \f([0, M)\f) in Zeile `i`
   * dieser Matrix.
   */
  VectorView rowview(int i);

  /**
   * \brief Ergibt einen ConstVectorView auf eine Spalte dieser Matrix.
   * \param[in] j Der Index der Spalte, von der einen View genommen wird.
   * \returns Einen ConstVectorVew von den Indizes \f([0, N)\f) in Spalte `j`
   * dieser Matrix.
   */
  ConstVectorView ccolview(int j) const;

  /**
   * \brief Ergibt einen VectorView auf eine Spalte dieser Matrix.
   * \param[in] j Der Index der Spalte, von der einen View genommen wird.
   * \returns Einen VectorView von den Indizes \f([0, N)\f) in Spalte `j`
   * dieser Matrix.
   */
  VectorView colview(int j);

  /**
   * \brief Weist die Werte der Matrix \f(B\f) zu den entsprechenden Werte
   * dieser Matrix \f(A\f) zu.
   * \param[in] B die Matrix, die zu \f(A\f) zugewiesen wird.
   * \details Fürht die Zuweisung \f[A_{ij} = B_{ij}\f] aus.
   */
  void assign_other(Matrix const &B);

  /**
   * \brief Addiert die Werte der Matrix \f(B\f) von den entsprechenden
   * Werte dieser Matrix \f(A\f).
   * \param[in] B Die Matrix, die zu \f(A\f) addiert wird.
   * \details Fürht die Zuweisung \f[A_{ij} = A_{ij}+B_{ij}\f] aus.
   */
  void add_assign_other(Matrix const &B);

  /**
   * \brief Subtrahiert die Werte der Matrix \f(B\f) von den entsprechenden
   * Werte dieser Matrix \f(A\f).
   * \param[in] B Die Matrix, die von \f(A\f) subtrahiert wird.
   * \details Fürht die Zuweisung \f[A_{ij} = A_{ij}-B_{ij}\f] aus.
   */
  void subtract_assign_other(Matrix const &B);

  /**
   * \brief Skaliert die Werte dieser Matrix \f(A\f) um \f(a\f).
   * \param[in] a Der Wert, von dem die Werte dieser Matrix skaliert wird.
   * \details Fürht die Zuweisung \f[A_{ij} = a*A_{ij}\f] aus.
   */
  void assign_scalar_multiply(double a);
};

// arithmetic

/**
 * \brief Berechnet \f(w_i = u_i + v_i\f) und ergibt das Ergebnis als Vector.
 */
Vector add(VectorLike const &u, VectorLike const &v);

/**
 * \brief Berechnet \f(C_{ij} = A_{ij} + B_{ij}\f) und ergibt das Ergebnis als
 * Matrix.
 */
Matrix add(Matrix const &A, Matrix const &B);

/**
 * \brief Berechnet \f(w_i = u_i - v_i\f) und ergibt das Ergebnis als Vector.
 */
Vector subtract(VectorLike const &u, VectorLike const &v);

/**
 * \brief Berechnet \f(C_{ij} = A_{ij} - B_{ij}\f) und ergibt das Ergebnis als
 * Matrix.
 */
Matrix subtract(Matrix const &A, Matrix const &B);

/**
 * \brief Berechnet das Skalarprodukt \f(s = \sum_iu_iv_i\f) und ergibt das
 * Ergebnis als double.
 */
double scalar_product(VectorLike const &u, VectorLike const &v);

/**
 * \brief Berechnet das Produkt \f(w_i = s * u_i\f) und ergibt das
 * Ergebnis als Vector.
 */
Vector scalar_multiply(VectorLike const &u, double s);

/**
 * \brief Berechnet \f(B_{ij} = s*B_{ij}\f) und ergibt das Ergebnis als Matrix.
 */
Matrix scalar_multiply(Matrix const &A, double s);

/**
 * \brief Berechnet das Produkt \f(c_i = \sum_jA_{ij}b_j\f) und ergibt das
 * Ergebnis als Vector.
 */
Vector matrix_vector_prod(Matrix const &A, VectorLike const &b);

/**
 * \brief Berechnet das Produkt \f(C_{ij} = \sum_kA_{ik}B_{kj}\f) und ergibt das
 * Ergebnis als Matrix.
 */
Matrix matrix_matrix_prod(Matrix const &A, Matrix const &B);

// i-o
/**
 * \brief Fügt die Werte in dem VectorLike `v` mittels `>>` sinnvoll in `out`
 * ein.
 */
void print_vectorlike_to(VectorLike const &v, std::ostream &out);

/**
 * \brief Fügt die Werte in der Matrix `m` mittels `>>` sinnvoll in `out` ein.
 */
void print_matrix_to(Matrix const &m, std::ostream &out);

} // namespace linalg