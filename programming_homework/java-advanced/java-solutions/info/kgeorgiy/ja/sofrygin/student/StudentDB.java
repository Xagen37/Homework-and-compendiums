package info.kgeorgiy.ja.sofrygin.student;

import info.kgeorgiy.java.advanced.student.GroupName;
import info.kgeorgiy.java.advanced.student.Student;
import info.kgeorgiy.java.advanced.student.StudentQuery;

import java.util.*;
import java.util.function.BinaryOperator;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class StudentDB implements StudentQuery {
    private static final Comparator<Student> COMPARE_BY_NAME =
            Comparator.comparing(Student::getLastName)
                    .thenComparing(Student::getFirstName)
                    .reversed()
                    .thenComparingInt(Student::getId);

    private static <T, E> Stream<T> getMappedStreamFrom(final Collection<E> collection, final Function<E, T> mapFunc) {
        return collection.stream().map(mapFunc);
    }

    private static <T, E> List<T> getMappedListFrom(final Collection<E> collection, final Function<E, T> mapFunc) {
        return getMappedStreamFrom(collection, mapFunc).collect(Collectors.toList());
    }

    @Override
    public List<String> getFirstNames(final List<Student> students) {
        return getMappedListFrom(students, Student::getFirstName);
    }

    @Override
    public List<String> getLastNames(final List<Student> students) {
        return getMappedListFrom(students, Student::getLastName);
    }

    @Override
    public List<GroupName> getGroups(final List<Student> students) {
        return getMappedListFrom(students, Student::getGroup);
    }

    @Override
    public List<String> getFullNames(final List<Student> students) {
        return getMappedListFrom(students, student -> student.getFirstName() + ' ' + student.getLastName());
    }

    @Override
    public Set<String> getDistinctFirstNames(final List<Student> students) {
        return getMappedStreamFrom(students, Student::getFirstName)
                .collect(Collectors.toCollection(TreeSet::new));
    }

    @Override
    public String getMaxStudentFirstName(final List<Student> students) {
        return students.stream()
                .max(Student::compareTo)
                .map(Student::getFirstName)
                .orElse("");
    }

    private static <T> List<T> sortCollectionBy(final Collection<T> collection, final Comparator<T> comp) {
        return collection.stream()
                .sorted(comp)
                .collect(Collectors.toList());
    }

    @Override
    public List<Student> sortStudentsById(final Collection<Student> students) {
        return sortCollectionBy(students, Comparator.comparingInt(Student::getId));
    }

    @Override
    public List<Student> sortStudentsByName(final Collection<Student> students) {
        return sortCollectionBy(students, COMPARE_BY_NAME);
    }

    private static Stream<Student> getStudentsStreamByPredicate(final Collection<Student> students, final Predicate<Student> predicate) {
        return students.stream()
                .filter(predicate)
                .sorted(COMPARE_BY_NAME);
    }

    private static List<Student> getStudentsListByPredicate(final Collection<Student> students, final Predicate<Student> predicate) {
        return getStudentsStreamByPredicate(students, predicate)
                .collect(Collectors.toList());
    }

    private static <T> List<Student> findStudentsBy(final Collection<Student> students, final Function<Student, T> extractor, final T test) {
        return getStudentsListByPredicate(students, student -> extractor.apply(student).equals(test));
    }

    @Override
    public List<Student> findStudentsByFirstName(final Collection<Student> students, final String name) {
        return findStudentsBy(students, Student::getFirstName, name);
    }

    @Override
    public List<Student> findStudentsByLastName(final Collection<Student> students, final String name) {
        return findStudentsBy(students, Student::getLastName, name);
    }

    @Override
    public List<Student> findStudentsByGroup(final Collection<Student> students, final GroupName group) {
        return findStudentsBy(students, Student::getGroup, group);
    }

    @Override
    public Map<String, String> findStudentNamesByGroup(final Collection<Student> students, final GroupName group) {
        return getStudentsStreamByPredicate(students, student -> student.getGroup().equals(group))
                .collect(Collectors.toMap(
                        Student::getLastName,
                        Student::getFirstName,
                        BinaryOperator.minBy(String::compareTo)
                ));
    }
}
